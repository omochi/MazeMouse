#include<stdio.h>

class A{
	public:
		~A(){
			printf("%s\n",__PRETTY_FUNCTION__);	
		}
		
};

class B : public A{
	public:
		virtual ~B(){
			printf("%s\n",__PRETTY_FUNCTION__);
		}
};

class C : public B{
	public:
		virtual ~C(){
			printf("%s\n",__PRETTY_FUNCTION__);
		}
};

int main(int argc,char *argv[]){
	A *c = new C();
	B *c2=new C();

	delete c;
	delete c2;
	return 0;
}
