/*-
 * Copyright (c) 2014 Spectra Logic Corporation. All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: releng/10.2/sbin/devd/tests/client_test.c 270242 2014-08-20 19:30:58Z asomers $");

#include <stdbool.h>
#include <stdio.h>

#include <sys/param.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <atf-c.h>
/* Helper functions*/

/*
 * Create two devd events.  The easiest way I know of, that requires no special
 * hardware, is to create md(4) devices.
 */
static void
create_two_events(void)
{
	FILE *create_stdout;
	FILE *destroy_stdout;
	char mdname[80];
	char destroy_cmd[80];
	char *error;

	create_stdout = popen("mdconfig -a -s 64 -t swap", "r");
	ATF_REQUIRE(create_stdout != NULL);
	error = fgets(mdname, sizeof(mdname), create_stdout);
	ATF_REQUIRE(error != NULL);
	/* We only expect one line of output */
	ATF_REQUIRE_EQ(0, pclose(create_stdout));

	snprintf(destroy_cmd, nitems(destroy_cmd), "mdconfig -d -u %s", mdname);
	destroy_stdout = popen(destroy_cmd, "r");
	/* We expect no output */
	ATF_REQUIRE_EQ(0, pclose(destroy_stdout));
}

/*
 * Test Cases
 */

/*
 * Open a client connection to devd, create some events, and test that they can
 * be read _whole_ and _one_at_a_time_ from the socket
 */
ATF_TC_WITHOUT_HEAD(seqpacket);
ATF_TC_BODY(seqpacket, tc)
{
	int s;
	int error;
	struct sockaddr_un devd_addr;
	bool got_create_event = false;
	bool got_destroy_event = false;
	const char create_pat[] =
		"!system=DEVFS subsystem=CDEV type=CREATE cdev=md";
	const char destroy_pat[] =
		"!system=DEVFS subsystem=CDEV type=DESTROY cdev=md";

	memset(&devd_addr, 0, sizeof(devd_addr));
	devd_addr.sun_family = PF_LOCAL;
	strlcpy(devd_addr.sun_path, "/var/run/devd.seqpacket.pipe",
			sizeof(devd_addr.sun_path));

	s = socket(PF_LOCAL, SOCK_SEQPACKET, 0);
	ATF_REQUIRE(s >= 0);
	error = connect(s, (struct sockaddr*)&devd_addr, SUN_LEN(&devd_addr));
	ATF_REQUIRE_EQ(0, error);

	create_two_events();

	/*
	 * Loop until both events are detected on _different_ reads
	 * There may be extra events due to unrelated system activity
	 * If we never get both events, then the test will timeout.
	 */
	while (!(got_create_event && got_destroy_event)) {
		int cmp;
		ssize_t len;
		char event[1024];

		len = recv(s, event, sizeof(event), MSG_WAITALL);
		ATF_REQUIRE(len != -1);
		/* NULL terminate the result */
		event[len] = '\0';
		printf("%s", event);
		cmp = strncmp(event, create_pat, sizeof(create_pat) - 1);
		if (cmp == 0)
			got_create_event = true;

		cmp = strncmp(event, destroy_pat, sizeof(destroy_pat) - 1);
		if (cmp == 0)
			got_destroy_event = true;
	}
}

/*
 * Open a client connection to devd using the stream socket, create some
 * events, and test that they can be read in any number of reads.
 */
ATF_TC_WITHOUT_HEAD(stream);
ATF_TC_BODY(stream, tc)
{
	int s;
	int error;
	struct sockaddr_un devd_addr;
	bool got_create_event = false;
	bool got_destroy_event = false;
	const char create_pat[] =
		"!system=DEVFS subsystem=CDEV type=CREATE cdev=md";
	const char destroy_pat[] =
		"!system=DEVFS subsystem=CDEV type=DESTROY cdev=md";
	ssize_t len = 0;

	memset(&devd_addr, 0, sizeof(devd_addr));
	devd_addr.sun_family = PF_LOCAL;
	strlcpy(devd_addr.sun_path, "/var/run/devd.pipe",
			sizeof(devd_addr.sun_path));

	s = socket(PF_LOCAL, SOCK_STREAM, 0);
	ATF_REQUIRE(s >= 0);
	error = connect(s, (struct sockaddr*)&devd_addr, SUN_LEN(&devd_addr));
	ATF_REQUIRE_EQ(0, error);

	create_two_events();

	/*
	 * Loop until both events are detected on _different_ reads
	 * There may be extra events due to unrelated system activity
	 * If we never get both events, then the test will timeout.
	 */
	while (!(got_create_event && got_destroy_event)) {
		char event[1024];
		ssize_t newlen;
		char *create_pos, *destroy_pos;

		newlen = read(s, &event[len], sizeof(event) - len);
		ATF_REQUIRE(newlen != -1);
		len += newlen;
		/* NULL terminate the result */
		event[newlen] = '\0';
		printf("%s", event);

		create_pos = strstr(event, create_pat);
		if (create_pos != NULL)
			got_create_event = true;

		destroy_pos = strstr(event, destroy_pat);
		if (destroy_pos != NULL)
			got_destroy_event = true;

	}
}

/*
 * Main.
 */

ATF_TP_ADD_TCS(tp)
{
	ATF_TP_ADD_TC(tp, seqpacket);
	ATF_TP_ADD_TC(tp, stream);

	return (atf_no_error());
}

