#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <string>
#include <map>

/*  para garantizar 60 frames por segundo se necesita recalcular cada ecena en menos de 16 ms  */
using namespace std;

typedef map<string, map<string,int>*> adyacencia; //<elemento, vertices>
typedef pair<string, map<string,int>*> im;
typedef pair<string, int> si;
FILE * pFile;
adyacencia  ady;
vector<pair<string, string> > relaciones;
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
		s->insert(si(b, 0));
		ady.insert(im(a, s));
		return 0;
	}
	else
	{
		p->second->insert(si(b,0));
		return 1;
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
	int size_elementos = elementos.size();
	for(int i = 0; i < size_elementos; i++)
	{
		if(!adyaccencia_a_b(elementos.at(i), elementos.at(i))) return false;
	}
	return true;
}
bool simetria()
{
	int size_relaciones = relaciones.size();
	for(int i = 0; i < size_relaciones; i++)
	{
		if(!adyaccencia_a_b(relaciones.at(i).second, relaciones.at(i).first)) return false;
	}
	return true;
}
bool antisimetria()
{
	int size_relaciones = relaciones.size();
	for(int i = 0; i < size_relaciones; i++)
	{
		if(adyaccencia_a_b(relaciones.at(i).second, relaciones.at(i).first)&&relaciones.at(i).first.compare(relaciones.at(i).second)) return false;
	}
	return true;
}
/*
(a,b) y (b, c) -> (a,c)
1- obtener todos los elementos b que se relacionan con a 
2- obtener todos los elementos c que se relacionan con b allado en 1-
3- verificar si (a,c) para cada c allado en 2 se cumple (a,c) 

*/
bool transitividad()
{
    map<string,int>* b;
    map<string,int>::iterator q ;
	vector< map<string,int>*> c;
	int relaciones_size = relaciones.size();
	
	for(int i=0; i<relaciones_size; i++){
	   	map<string, map<string,int>*>::iterator p = ady.find(relaciones.at(i).first);
        b=p->second;
         
       	std::map<string,int>::const_iterator
    mit=b->begin(),
    mend=b->end();
    
  for(;mit!=mend;++mit) 
             {
				 printf("b tiene %s", mit->first.c_str());
				 c.push_back(ady.find(mit->first)->second);
			 }
			 
          for (int j = 0; j<c.size(); j++)
             {
				 std::map<string,int>::const_iterator
    mit2 (c.at(j)->begin()),
    mend2(c.at(j)->end());
  for(;mit2!=mend2;++mit2) 
				
             {
				if(!adyaccencia_a_b(relaciones.at(i).first, q->first)) return false;
				  
			 }
				  
			 }
              c.clear();
         
	}
	return true;
}
void ingresar_elementos_relaciones()
{
	char tmp_c[256], tmp_c2[256];
	string tmp, tmp2;
	fscanf(pFile, "%d",&n_elementos);
	for(int i =0; i<n_elementos;i++)
	{
	fscanf(pFile,"%s", tmp_c);
	tmp = tmp_c;
	elementos.push_back(tmp_c);
    }
	fscanf(pFile,"%d", &n_elementos);
	for(int i =0; i < n_elementos;i++)
	{
		fscanf(pFile,"%s %s", tmp_c, tmp_c2);
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
	pFile = fopen ("elementos_relaciones.txt","r");
    rewind (pFile);
	ingresar_elementos_relaciones();
	printf("reflexividad: %d \n", reflexividad());
	printf("simetria: %d \n", simetria());
	printf("antisimetria: %d \n", antisimetria());
	printf("transitividad: %d \n", transitividad());
	fclose (pFile);
	return 0;
}
