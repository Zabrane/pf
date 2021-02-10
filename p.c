//! nolibc printf copyright (c) 2020 regents of kparc, bsd-2-clause

#include"_.h"

//! itoa atoi hex strlen
ZI iS(UI y,S x){P(!y,*x='0',1)I n;_N(n=1+lg10(y),x[i]='0'+y%10ul;y/=10)R n;}ZI sln(S s){I r=0;W(*s++)r++;R r;}ZG ib[11]="-";
UI sI(S a,I*n){G c;UI i=0,r=*n=0;W((c=*a++)&&IN('0',c,'9'))i++,r=r*10u+((UI)c-'0');R*n=i,r;}ZS hh(S s,G c);ZG xb[26];
ZI jX(J j){S s=xb+25;J k=j;do hh(s-=2,k);W(k>>=8);R 25-(s-xb);}ZS hh(S s,G c){N(2,G a=i?c&15:c>>4;s[i]="0W"[9<a]+a)R s;}

//! (tx)byte (txn)bytes (txN)times (b)yte (i)nt he(x) (s)tr (p)ad (nl)ine
ZI tx(G c){R write(1,&c,1);}ZI txn(S x,I n){P(!n,n)N(n,tx(x[i]));R n;}ZI txN(G c,I n){N(n,tx(c))R n;}
ZI txp(S x,I n,I p){R txN(' ',MX(0,p-n))+txn(x,n)+txN(' ',ABS(MN(0,p+n)));}ZI txb(G c,I p){R txp(&c,1,p);}ZI nl(){R tx('\n');}
ZI txx(J j,I p){I n=jX(j)+2;S b=xb+25-n;*b='0',b[1]='x';R txp(b,n,p);}ZI txi(I x,I p){G t=0>x,*s=ib+1;x=t+iS(ABS(x),s);R txp(s-t,x,p);}
ZI txs(S x,I p){R txp((S)x,sln(x),p);}

#define VMX 16
#define pf(f,a...) txpf(f,(J[VMX]){a}) //!< arguments of pf() as an array of void ptrs, up to VMX
#define va(c,t,f) C(c,n+=f((t)(a[i++]),flg*flw);) //!< call f((type)nextarg,options)

//! %[fmt][flw][.prc]cdps
I txpf(S f,J a[VMX]){                 //!< (f)ormat string (aka tape), (a)rguments
 G c;I j,i=0,n=0;                     //!< total le(n)gth, arg(i)ndex, curr(c)har
 UI flg,flw,prc;                      //!< fmt flags, field width, precision
 W(c=*f++){                           //!< while more chars left on tape,
  flg=prc=0,flg=j=1;                  //!< reset state, then:
  Z('%'-c,tx(c)){                     //!< echo c unless %, otherwise:
   W(j)SW(c=*f,C('-',flg=-1,f++),j=0) //!< scan flags (%flg)
   flw=sI(f,&j),f+=j,c=*f;            //!< scan field width (%[]flw)
   Z('.'==c,f++;prc=sI(f,&j))c=*f;    //!< scan precision (%[].prc)
   W('l'==c||'h'==c)c=*++f;           //!< skip [lh..] nyi
    SW(c,                             //!< dispatch by type:
     C('%',tx(c))                     //!< %% is literal %
     va('c',G,txb)                    //!< char
     va('d',I,txi)                    //!< int32
     va('p',J,txx)                    //!< pointer
     va('s',S,txs))                   //!< string
    f++;}}R n;}                       //!< advance

I main(I c,char**a){I n;S ti,t[]={"atw","nsl","attila","icsa","alex","kparc"};nl();

  N(6,ti=t[i],n=sln(ti);pf("%3d|%-8s|%8s|%3d|%-3d|%12p|%-5p|%3c|%-3c|%%|\n",i,ti,ti,n,n,0xdeadbeef,0x04,'k','k'))

  pf(" n=(%d) %s\n\n",
   pf("\n pf: d=(%d %d) s=(%s %s %s) p=(0x%p) c=(%c) eot=(0x%p)",
    -2147483647, 2147483647,"i uncover", "the soul-destroying", "abhorrence",0xcafebabe,'K',0x04),
  "//:~");R 0;}

//:~
