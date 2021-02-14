//! nolibc printf(3), copyright (c) 2020 regents of kparc, bsd-2-clause

#pragma once
#ifndef PF_H
#define PF_H

#define PFV 1
#define PFVM 0
#define PFL "(c) 2020 kparc / bsd"

#ifndef NOPF
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wint-conversion"
#pragma GCC diagnostic ignored "-Wpedantic"

#define printf pf   //!< use pf(f,a..)

#if defined(__TINYC__)
#ifndef PFMX
#define PFMX 8      //!< under tcc, max argcount is mandatory
#pragma message("PFMX is mandatory under tcc, using default of 8")
#endif
#define PFSZ PFMX
#else
#define PFMX 0      //!< for gcc/clang, argcount is unbound
#define PFSZ
#endif

#ifndef PFCH
#define PFCH 0      //!< if f < 128, treat it as char (transmit and return 1)     (!posix)
#endif

#if NOLC            //!< satisfy minimal freestanding environment
#include<string.h>
#define strlen slen
void *memset(void *d, int c, size_t n)            {char*s=(char*)d;while(n--)*s++=c;return d;}
void *memcpy(void *d, const void *s, size_t n)    {char*x=(char*)d,*y=(char*)s;while(n--)*x++=*y++;return d;}
void exit(int);
#endif

//! modify below this line at your own risk. stay social, reach out.

#include"_.h"
#include<unistd.h> //!< write(2)
typedef union{UJ uj;}arg;typedef arg args[PFSZ];                          //!< use union to avoid gcc bug
#define PU(f,t) ZZ S f(S s,t i){t j;do*--s='0'+i-10*(j=i/10);W(i=j);R s;} //!< parse signed/unsigned
#define TU(f,t,u) ZZ I f(t x,I p,I l){I n;S r=jS(x,&n,u);R txp(r,n,p);}   //!< tramsmit signed/unsigned

//! strlen [u]ltoa ato[u]l hex
ZG xb[26];ZI slen(char*s){I r=0;W(*s++)r++;R r;}ZS ng(S s){R*--s='-',s;}PU(pj,J)PU(pu,UJ);
ZS jS(UJ i,I*n,G u){S r=(!u&&0>(J)i)?ng(jS(-i,n,u)):u?pu(xb+25,i):pj(xb+25,i);R*n=25+(xb-r),r;}
UI sI(char*a,I*n){G c;UI i=0,r=*n=0;W((c=*a++)&&IN('0',c,'9'))i++,r=r*10u+((UI)c-'0');R*n=i,r;}ZS hh(S s,G c);
ZS hh(S s,G c){N(2,G a=i?c&15:c>>4;s[i]="0W"[9<a]+a)R s;}ZI jX(UJ j){S s=xb+25;UJ k=j;do hh(s-=2,k);W(k>>=8);R 25-(s-xb);}

//! (tx)byte (txn)bytes (txN)times (b)yte (i)nt he(x) (s)tr (p)ad
ZI tx(G c){R write(1,&c,1);}ZI txn(S x,I n){P(!n,n)N(n,tx(x[i]));R n;}ZI txN(G c,I n){N(n,tx(c))R n;}
ZI txp(S x,I n,I p){R txN(' ',MX(0,p-n))+txn(x,n)+txN(' ',ABS(MN(0,p+n)));}ZI txb(G c,I p,I l){R txp(&c,1,p);}
ZI txx(UJ j,I p,I l){I n=jX(j)+2;S b=xb+25-n;*b='0',b[1]='x';R txp(b,n,p);}TU(txj,J,0)TU(txu,UJ,1)
ZI txs(char*x,I p,I l){R txp((S)x,l?l:slen(x),p);}

#ifdef __TINYC__
#define NRg(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,N,...) N
#define NRG(...) NRg(__VA_ARGS__, 16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1)
#define pf(f,a...) ({args pfa={a};txpf(f,pfa,NRG(a));})    //!< coerce arguments of pf() to a stack array of unsigned long longs
#else
#define pf(f,a...) ({args pfa={a};txpf(f,pfa,CNT(pfa));})  //!< coerce arguments of pf() to a stack array of unsigned long longs
#endif
#define vnx(r)     r=a[i++].uj                             //!< retrieve next positional arg
#if PFMX
#define varg(r)    P(PFMX==i,n)vnx(r)                      //!< check PFMX overflow
#else
#define varg(r)    vnx(r)
#endif
#define vtx(f,a)   n+=f(a,flg*flw,prc);
#define va(c,t,f)  C(c,{t _a;varg(_a);vtx(f,_a)})          //!< call f((type)nextarg,options)
#define nx continue

#define si(s,i)   (txs(s,0,0),txj(i,0,0))

//! %[%-][09..][.09..*]dcups
I txpf(char *f,args a,I ac){             //!< (f)ormat string (aka tape), (a)rguments, (a)rg(c)ount
 P(PFCH&&(char*)128>f,tx(*(G*)&f))       //!< optional char check for f, see FCH
 G c;I j,i=0,n=0;                        //!< total le(n)gth, arg(i)ndex, curr(c)har
 UI flg,flw,prc;                         //!< fmt flags, field width, precision
 W(c=*f++){                              //!< while more chars left on tape,
  flg=prc=0,flg=j=1;                     //!< reset state, then:
  Z('%'-c,n+=tx(c);nx)                   //!< echo c unless %, otherwise:
  W(j)SW(c=*f,C('-',flg=-1,f++),j=0)     //!< scan flags (%flg)
  flw=sI(f,&j),f+=j,c=*f;                //!< scan field width (%flw)
  Z('.'==c,prc=sI(++f,&j);f+=j;c=*f;     //!< scan precision (%.prc)
   Z(!j,Z('*'-c,f++;nx)                  //!< %.[not 09*] is empty field
    c=*++f;varg(prc)))c=*f;              //!< scan positional precision (%.*)
  W('l'==c||'h'==c)c=*++f;               //!< skip [lh..] nyi
  //txs("\nline: ",0,0),txs(f,0,slen(f)-1),si(" ac: ",ac),si(" i: ",i),tx('\n');
  Z(ac==i,vtx(txs,"(null)"))             //!< output (null) on argcount overflow
  SW(c,                                  //!< dispatch by conversion specifier:
   va('c',G,txb)va('d',J,txj)va('u',UJ,txu)
   va('p',UJ,txx)va('s',char*,txs)C('%',tx(c)))
  f++;}R n;}

#pragma GCC diagnostic pop
#else
#include<string.h>                       //!< use stock printf
#endif//NOPF

#endif//PF_H

//:~
