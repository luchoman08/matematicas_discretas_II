#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <string>
#include <map>
#include <algorithm>    // std::find
/*  para garantizar 60 frames por segundo se necesita recalcular cada ecena en menos de 16 ms  */
using namespace std;

typedef map<string, vector<string> > adyacencia; //<elemento, vertices>
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
    adyacencia::iterator p = ady.find(a);
	if(p == ady.end())
	{
		vector<string> s;
		
		s.push_back(b);
		ady.insert(make_pair(a, s));
		return 0;
	}
	else
	{
		p->second.push_back(b);
		return 1;
	}
}
bool adyaccencia_a_b(string a, string b)
{
  adyacencia::iterator p = ady.find(a);
  if(p==ady.end())
  return false;
  else
  {
	  
	 std::vector<string>::iterator q;
     q = find(p->second.begin(), p->second.end(), b);
	 if(q==p->second.end())
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
//bool simetria()
//{
//	int size_relaciones = relaciones.size();
//	for(int i = 0; i < size_relaciones; i++)
//	{
//		if(!adyaccencia_a_b(relaciones.at(i).second, relaciones.at(i).first)) return false;
//	}
//	return true;
//}
//bool antisimetria()
//{
//	int size_relaciones = relaciones.size();
//	for(int i = 0; i < size_relaciones; i++)
//	{
//		if(adyaccencia_a_b(relaciones.at(i).second, relaciones.at(i).first)&&relaciones.at(i).first.compare(relaciones.at(i).second)) return false;
//	}
//	return true;
//}
/*
(a,b) y (b, c) -> (a,c)
1- obtener todos los elementos b que se relacionan con a 
2- obtener todos los elementos c que se relacionan con b allado en 1-
3- verificar si (a,c) para cada c allado en 2 se cumple (a,c) 

*/
bool transitividad()
{
    vector<string> b;
    map<string,vector<string> >::iterator q ;
	vector<string> c;
	 c.erase(c.begin(), c.end());
	int relaciones_size = relaciones.size();
	
	for(int i=0; i<relaciones_size; i++){
	   	map<string, vector<string> >::iterator p = ady.find(relaciones.at(i).first);
       b=p->second;
        
     //  printf("tamaño de b para b= %s: %d\n",relaciones.at(i).first.c_str(),b.size()); 
          for(int j=0; j<b.size(); j++)
          {
			  adyacencia::iterator r = ady.find(b.at(j));
			  if(r!=ady.end()){
			  //printf("el r tiene como tamaño: %d\n", r->second.size());
			  c.insert(c.end(),r->second.begin(),r->second.end());
		  }
		  } 
	
       for(int j=0; j<c.size(); j++) {
			if(!adyaccencia_a_b(relaciones.at(i).first, c.at(j))) return false;
				//  printf("valores para %s: %s\n", relaciones.at(i).first.c_str(), c.at(j).c_str());
			 }
				  
		 
             c.erase(c.begin(), c.end());
         
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
//	printf("simetria: %d \n", simetria());
//	printf("antisimetria: %d \n", antisimetria());
	printf("transitividad: %d \n", transitividad());
	fclose (pFile);
	return 0;
}
