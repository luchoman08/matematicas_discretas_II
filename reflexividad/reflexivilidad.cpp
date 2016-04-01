#include <stdio.h>
#include <vector>
#include <utility>
#include <string>
#include <map>
using namespace std;

typedef map<string, map<string,int>*> adyacencia; //<elemento, vertices>
typedef pair<string, map<string,int>*> ii;
typedef pair<string, int> iii;
adyacencia  ady;
vector<pair<string, string>> relaciones;
vector<string> elementos;
int n_elementos =0;
/*
 * 			programa que permite saber si un conjunto cumple con la propiedad reflexiva o no
 * 
*/



int adicionar_tupla(string a, string b)
{
	map<string, map<string,int>*>::iterator p = ady.find(a);
	if(p == ady.end())
	{
		map<string,int>* s = new map<string,int> ;
		ady.insert(ii(a, s));
		return 0;
	}
	else
	{
		p->second->insert(iii(b,0));
		return 1;
	}
}
void ingresar_elementos()
{
	char tmp_c[256];
	string tmp;
	scanf("%d",&n_elementos);
	for(int i =0; i<n_elementos;i++)
	{
	scanf("%s", tmp_c);
	tmp = tmp_c;
	elementos.push_back(tmp_c);
    }
}
bool adyaccencia_a_b(string a, string b)
{
  map<string, map<string,int>*>::iterator p = ady.find(a);
  if(p==ady.end())
  return false;
  else
  {
	 map<string,int>::iterator q = p->second->find(b);
	 if(q==p->second->end())
	 return false;
	 else 
	 return true;
  }
}
bool reflexividad()
{
	for(int i = 0; i < elementos.size(); i++)
	{
		if(!adyaccencia_a_b(elementos.at(i), elementos.at(i))) return false;
	}
	return true;
}
void ingresar_tuplas_relacion()
{
	char tmp_c[256], tmp_c2[256];
	string tmp, tmp2;
	scanf("%d", &n_elementos);
	for(int i =0; i < n_elementos;i++)
	{
		scanf("%s %s", tmp_c, tmp_c2);
		tmp = tmp_c; tmp2 = tmp_c2;
		adicionar_tupla(tmp, tmp2);
		relaciones.push_back(make_pair(tmp, tmp2));
	}
}
void print_elementos()
{
	int size_elementos = elementos.size();
	for(int i=0; i<size_elementos;i++)
	printf("%s\n", elementos.at(i).c_str());
}
int main (int args, char** argv){
	ingresar_elementos();
	ingresar_tuplas_relacion();
	printf("%d", reflexividad());
	return 0;
}
