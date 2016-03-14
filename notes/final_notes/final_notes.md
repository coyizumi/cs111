RSA: Requires trapdoor function

* easy one way, hard other, unelss you have special trapdoor info

* m ^ (e*d) mod N = m

* N = p * q
* Keep N,p,q secret

* Phi = P-1
* Phi (a*b) = 

* Phi(N) = (P1-1) * (P2-1)

* d = (k * phi(n) + 1) / e

* p1 = 53
* p2 = 59
* n = 53*59 = 3127
* Phi(n) = 3016
* e = 3
* d = (2 * (3016) + 1) / 3 = 2011

* N and E make up public key

Bob locks message:
m ^ e MOD n = c

* Alice decrypts: 

* c^d MOD N = m

* Duffie:

* modulus p, base g
* secret a,b

* Alice send:
* A=g^a mod p 

* Bob send:
* B=g^b mod p 

* Alice computes:
* s = B^a mod p 

* Bob computes:
* s = A^b mod p 

* s is secret number
