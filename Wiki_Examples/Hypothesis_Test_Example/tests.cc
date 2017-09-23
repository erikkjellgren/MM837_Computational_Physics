#include "Week36.cc"
#include <rapidcheck.h>

int main(){
	rc::check("sinus function", [](double x){
		RC_ASSERT(sinus_thr(x, 1e-12)<=1.0);
		RC_ASSERT(sinus_thr(x, 1e-12)>=-1.0);
	});
	
	rc::check("sinus function no fac", [](double x){
		RC_ASSERT(sinus_thr_nofac(x, 1e-12)<=1.0);
		RC_ASSERT(sinus_thr_nofac(x, 1e-12)>=-1.0);
	});
	
	rc::check("sinus function nofac identity", [](double x){
		RC_ASSERT(sinus_thr_nofac_identity(x, 1e-12)<=1.0);
		RC_ASSERT(sinus_thr_nofac_identity(x, 1e-12)>=-1.0);
	});
}