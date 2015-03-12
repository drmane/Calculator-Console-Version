#include<iostream>
#include<cstdlib>
#include<cmath>
#include<cctype>
#include<fstream>
using namespace std;

//Daniel Ruiz Manero
//Ricardo de la Rosa Vivas

int main(); //programa principal
char menu(char &opcion); //menu del programa principal
void calculadora(char s, char y, char p, char d, char e, char f, char z, char cancel, char salir, char memo, char smemo, ofstream &escrito); //opcion calculadora
void primerCaracter(double &operando1, double &memory, char &operador, char salir, char memo, char smemo, bool &error, bool &fin, ofstream &escrito); //estudio del primer caracter introducido
void operaciones1(double &operando1, double operando2, char operador, char s, char y, char p, char d, bool &error, ofstream &escrito); //operaciones de suma, resta, multiplicacion y division con sus respectivos errores
void operaciones2(double &operando1, double operando2, double &exponencial, char operador, char e, bool &error, ofstream &escrito); //operacion de exponencial con errores
void operaciones3(double &operando1, double &operando2, double &factorial, char operador, char f, char z, bool &error, ofstream &escrito); //operaciones de factorial y raiz cuadrada con errores
void erroresCalculadora(double &operando1, bool error, ofstream &escrito); //errores de la calculadora
void erroresCalculadoraMfracciones(int &numerador1, int &denominador1, bool error, ofstream &escrito); //errores de la calculadora en el modo fracciones
void calculadoraMfracciones(char s, char y, char p, char d, char e, char cancel, char salir, char simplificar, ofstream &escrit, char memo, char smemo); //opcion calculadora modo fracciones
void FprimerCaracter(int &numerador1,int &denominador1, char &operador, char &salir, bool &error,bool &fin, ofstream &escrito,char y,char s,char separador,char &cancel,char p,char d,char e,char simplificar,char memo, char smemo,int &memoryN,int &memoryD); //estudio del primer caracter introducido en el modo fracciones
void mcm(int denominador1, int denominador2, int &MCM, int MCD); //funcion minimo comun multiplo
void mcd(int denominador1, int denominador2, int &MCD); //funcion maximo comun divisor
void Fsuma(int &numerador1,int numerador2, int &denominador1, int denominador2, int MCM, int MCD); //operacion de fracciones, suma
void Fresta(int &numerador1,int numerador2, int &denominador1, int denominador2, int MCM, int MCD); //operacion de fracciones, resta
void Fmulti(int &numerador1,int numerador2,int &denominador1, int denominador2); //operacion de fracciones, multiplicacion
void Fdivi(int &numerador1,int numerador2,int &denominador1, int denominador2); //operacion de fracciones, division
void FpotenG(int &numerador1,int &denominador1, int denominador2,bool &error,ofstream &escrito);//operancion potencia general
void FpotenN(int &numerador1,double numerador2,int denominador1, int denominador2,bool &error,ofstream &escrito); //operacion de fracciones, potencia numerador
void FpotenD(int auxP,double numerador2,int &denominador1, int denominador2,bool &error,ofstream &escrito); //operacion de fracciones, potencia denominador
void Fsimpli(int &numerador1,int &denominador1, int MCD); //operacion de fracciones, simplificacion
void configuracion(char &s, char &y, char &p, char &d, char &e, char &f, char &z, char &cancel, char &salir, char &memo, char &smemo, char &simplificar);// opcion configuracion(la eleccion de lo que vamos a modificar se hace aqui)
void configuracionMenu(char &opcionConf, char &enter); //texto mostrado en pantalla de la configuracion y eleccion del menu
char cambioConf(char &operador);//funcion que cambia el operador de una operacion
		
	int main()
	{//menu principal
		char s,y,p,d,e,f,z,cancel,salir,memo,smemo,simplificar;
		char opcion;
		bool salirPrograma = false; //controla si se quiere salir del programa
		ifstream conf("conf.txt");//variable que deaparece al salir de main (en configuracion es otra variable distinta pero con mismo nombre)
		ofstream escrito("log.txt");

		if(conf.is_open() == true) //carga de operadores del conf.text si existe
		{	
				conf >> s >> y >> p >> d >> e >> f >> z >> cancel >> salir >> memo >> smemo >> simplificar;
				conf.close();	
		}
		else s = '+', y = '-', p = '*', d = '/', e = '^', f = '!', z = 'r', cancel = 'c', salir = 'x', memo = 'm', smemo = 'n', simplificar = 's'; //carga de operadores predeterminados si conf.txt no existe
		do
		{
		menu(opcion); //texto a mostrar del menu principal y eleccion de la opcion
		
			switch(opcion)// elecciones del menu principal
			{
			case '1': calculadora(s,y,p,d,e,f,z,cancel,salir,memo,smemo,escrito); break;
			case '2': calculadoraMfracciones(s, y, p, d, e, cancel, salir,simplificar,escrito,memo,smemo); break;
			case '3': system("CLS");configuracion(s,y,p,d,e,f,z,cancel,salir,memo,smemo,simplificar); break;
			case '4': salirPrograma = true; break;
			default: break;
			}
		}while(salirPrograma == false);
		escrito.close();
		return 0;
	}
	char menu(char &opcion)
	{//menu del programa principal
		char enter;
		bool error;

		do
		{
			cout << "Calculadora 4.0" << endl;
			cout << "----------------" << endl << endl;
			cout << "1. Calculadora " << endl;
			cout << "2. Calculadora Modo Fracciones " << endl;
			cout << "3. Configuracion " << endl;
			cout << "4. Salir " << endl;

			cout << endl << endl << "Aclaratorias en modo fracciones:" << endl<< endl;
			cout << "La memoria guarda fracciones, no numeradores ni denominadores."<< endl;
			cout << "Colocar el negativo de la fraccion en el numerador, no en el denominador."<< endl;
		
			error = false; // para repetirlo
			cin >> opcion; //eleccion del menu principal
			cin.get(enter);
			cin.sync();
		
			if((opcion < '1')||(opcion > '4')||(enter != '\n'))
			{
				system("CLS");
				cout << "ERROR!! Introduce una opcion valida " << endl;
				error = true;
			}
		}while((opcion < '1')||(opcion > '4')||(error == true));

		return opcion;
	}
	void calculadora(char s, char y, char p, char d, char e, char f, char z, char cancel, char salir, char memo, char smemo, ofstream &escrito)
	{	//opcion calculadora
		double memory = 0, operando1 = 0, operando2, factorial, exponencial;
		char operador, operando2n;
		bool salirconfig = false, cerrar = false, terminar = false, error = false, finexpresion = false, fin = false;	
		
		escrito << "Abrir calculadora Normal" << endl <<"-----------------------------------" << endl;
		system("cls");
		operando1 = 0;
		cout << operando1 << endl;
		escrito << operando1 << endl << flush;
		do  // bucle que se repite mientras no se pulse la variable salir, es decir, 'x'
		{ 
			primerCaracter(operando1,memory,operador,salir,memo,smemo,error,fin,escrito);
			if (fin == false) 
			{ 
				while (operador != '\n' && error == false) //bucle que se repite mientras no se pulse la tecla enter
				{ 
					error = cin.fail();
					if (operador == s || operador == y || operador == p || operador == d || operador == e) 
					{ 
						operando2n = cin.peek(); //se mira si el operando es un numero o smemo
						if (operando2n == smemo) {
						operando2 = memory;
						cin.get(operando2n);  escrito << operando2n << flush;
						} 
						else { cin >> operando2; escrito << operando2 << flush; } 
						operaciones1(operando1, operando2, operador, s, y, p, d, error, escrito);
						operaciones2(operando1, operando2, exponencial, operador, e, error, escrito);
					} 
					else 
						operaciones3(operando1, operando2, factorial, operador,  f, z, error, escrito);
					if (operador == cancel) { system("cls"); operando1 = 0; escrito << endl << "Borrar"; }
					else if (operador == memo) memory = operando1; 
					else if(operador == smemo) operando1 = memory;
					else if((operador != s)&&(operador != y)&&(operador != p)&&(operador != d)&&(operador != e)&&(operador != f)&&(operador != z)&&(operador != cancel)&&(operador != salir)&&(operador != memo)&&(operador != smemo))
						error = true; //error en el caso de no introducir un operador correcto
					cin.get(operador);  escrito << operador << flush;					
				} 
				erroresCalculadora(operando1, error, escrito);
				cin.sync();
				cin.clear(); //aqui termina el bucle de operaciones				
			} else fin = true;
		}while(fin == false); 
		cin.clear(); 
		cin.sync();
		system("cls");
		
	} 
	void primerCaracter(double &operando1, double &memory, char &operador, char salir, char memo, char smemo, bool &error,bool &fin, ofstream &escrito)
	{ //estudio del primer caracter introducido
		operador = cin.peek(); // Se mira primer caracter y en funcion de lo que sea:
			if (operador == salir) 
			{ 
				fin = true;  //Salir al menu
				escrito << endl << operador << endl << flush; 
				escrito << endl <<"Salir al menu "<<endl << "-----------------------------------" << endl << endl << flush;
			} 
			else if (operador == smemo) 
			{ 
				operando1 = memory; // Guardar como operando1 el valor de la memoria
				cin.get(operador);
				escrito << operador << flush;
			} 
			else if ((operador >= '0' && operador <= '9') || operador == '.') 
			{ 
				cin >> operando1; // Operación normal 
				escrito << operando1 << flush;
				cin.get(operador);
				escrito << operador << flush;
			} 
			else 
			{ //Para cuando el primer caracter es un operador
				cin.get(operador);
				escrito << operador << flush; 
			}
				error = cin.fail() ; // Error si se introduce un caracter extraño
	}
	void operaciones1(double &operando1, double operando2, char operador, char s, char y, char p, char d, bool &error, ofstream &escrito)
	{//operaciones de suma, resta, multiplicacion y division con sus respectivos errores
		if (operador == s)      
		{
			operando1 = operando1 + operando2; 
		} 
		else if (operador == y) 
		{
			operando1 = operando1 - operando2;
		} 
		else if (operador == p) 
		{ 
			operando1 = operando1 * operando2;
		} 
		else if (operador == d) 
		{
			if (operando2 == 0) 
			{ 
				error = true; 
				cout << "El resultado de dividir entre 0 es infinito" << endl; 
				escrito << endl << "El resultado de dividir entre 0 es infinito"  << flush; 
			}
			else
				operando1 = operando1 / operando2;
		} 
	}
	void operaciones2(double &operando1, double operando2, double &exponencial, char operador, char e, bool &error, ofstream &escrito)
	{//operacion de exponencial con errores
		if (operador == e)
		{  
			if (operando2 == 0) operando1 = 1;
			else if (operando2 - floor(operando2) != 0) 
			{
				error =true;
				cout << "El exponente tiene que ser entero" << endl; //exponente entero positivo
				escrito << endl << "El exponente tiene que ser entero" << flush;
			}
			else if (operando2 == 1) 
			{
				operando1 = operando1;
			}
			else if (operando2 == -1) 
			{
				operando1 = 1 / operando1;
			}								 
			else if (operando2 >= 2) 
			{
				exponencial = operando1;
				while (operando2 > 1)
				{
					operando1 = operando1 * exponencial;
					operando2 = operando2 -1;
				}
			}
			else if (operando2 <= -2) 
			{ 
				exponencial = operando1;
				while (operando2 <= -2) 
				{
					operando1 = operando1 * exponencial;
					operando2 = operando2 + 1;
				} 
				operando1 = 1 / operando1;
			} 
			else error = true; 
		}
	}
	void operaciones3(double &operando1, double &operando2, double &factorial, char operador, char f, char z, bool &error, ofstream &escrito)
	{ //operaciones de factorial y raiz cuadrada con errores
		if (operador == z) 
		{ 
			if (operando1 < 0)
			{
				error = true; //raiz cuadrada de numeros negativos no posible
				cout << "La raiz cuadrada solo existe para numeros mayores o iguales a 0"<< endl;
				escrito << endl << "La raiz cuadrada solo existe para numeros mayores o iguales a 0" << flush;
			}
			else operando1 = sqrt(operando1); 
		}

		else if (operador == f) 
		{ 
			factorial = operando1;		
			if (operando1 < 0)
			{ 
				error = true;
				cout << "El factorial tiene que ser postivo" << endl;
				escrito << endl << "El factorial tiene que ser postivo"; //factorial siempre positivo
			}
			else if (operando1 - floor(operando1) != 0 ) 
			{
				error = true;
				cout << "El factorial tiene que ser un numero entero" << endl;
				escrito << endl << "El factorial tiene que ser un numero entero"; //factorial siempre con numeros enteros
			}
			else
			{
				while (factorial > 1)
				{													
					operando1 = operando1 * (factorial - 1);
					factorial = factorial - 1;
				}
			}
		}
	}
	void erroresCalculadora(double &operando1, bool error, ofstream &escrito)
	{
		if (error == false) 
		{ 
			cout << operando1 << endl;
			escrito <<"="<< operando1 << endl << flush;// Muestra el resultado de la operacion si no ha habido errores
		} 
		else 
		{ 
			operando1 = 0;
			cout << "ERROR!!" << endl << operando1 << endl; 
			escrito << "ERROR!!" << endl << flush;
			error = false;  //sirve para repetir la calculadora en el caso de que haya habido error
		} 		
	}
	void erroresCalculadoraMfracciones(int &numerador1, int &denominador1, bool error, ofstream &escrito)
	{
		if (error == false) 
		{ 
			cout << numerador1 <<"|" << denominador1 << endl;
			escrito << "="<< numerador1 <<"|" << denominador1  << endl << flush;// Muestra el resultado de la operacion si no ha habido errores
			cin.sync();
		} else 
		{ 
			numerador1 = 0;denominador1=1;
			cout << "ERROR!!" << endl <<  numerador1 <<"|" << denominador1 << endl; 
			escrito << "ERROR!!" << endl << flush;
			cin.sync();
			error = false;

		} 
	}
	void calculadoraMfracciones(char s, char y, char p, char d, char e, char cancel, char salir, char simplificar, ofstream &escrito, char memo, char smemo) //opcion calculadora modo fracciones
	{
		int numerador1=0, numerador2, denominador1=1, denominador2=1, MCM=0, MCD=0,memoryN=0,memoryD=1;
		char operador, separador ='|', operando;
		bool salirconfig = false, cerrar = false, terminar = false, error = false, finexpresion = false, fin = false;

		system("CLS");
		escrito << "Abrir calculadora Modo Fracciones" << endl <<"-----------------------------------" << endl << "0|1" << endl<< flush;
		cout << "0|1" << endl;
		do
		{
			FprimerCaracter(numerador1,denominador1,operador,salir,error,fin,escrito,y,s,separador,cancel,p,d,e,simplificar,memo,smemo,memoryN,memoryD);

			if (fin == false) 
			{ 
				while (operador != '\n' && error == false) 
				{ 
					error = cin.fail();
					if (operador == s || operador == y || operador == p || operador == d)//se mira si el operando es un numero o smemo
					{
						operando=cin.peek();
						if ((operando >= '0' && operando <= '9')||operando=='-')
						{
							cin >> numerador2;
							escrito << numerador2 << flush;
							separador=cin.peek();
							if (separador=='|')
							{
								cin.get (separador);
								escrito << separador << flush;
								operando=cin.peek();
								if ((operando >= '0' && operando <= '9')){
									cin >> denominador2;
									escrito << denominador2 << flush;
								}else error=true;
							}
							else denominador2 = 1;

							if(operador==s)Fsuma(numerador1,numerador2,denominador1,denominador2,MCM,MCD);	
							else if(operador==y)Fresta(numerador1,numerador2,denominador1,denominador2,MCM,MCD);
							else if(operador==p)Fmulti(numerador1,numerador2,denominador1,denominador2);
							else if(operador==d)Fdivi(numerador1,numerador2,denominador1,denominador2);
						}else if(operando==smemo)//si el operando es la memoria
						{
							numerador2=memoryN;
							denominador2=memoryD;
							cin.get(operando);  escrito << operando << flush;
							if(operador==s) Fsuma(numerador1,numerador2,denominador1,denominador2,MCM,MCD);	//operaciones para cuando el operando es la memoria
							else if(operador==y) Fresta(numerador1,numerador2,denominador1,denominador2,MCM,MCD);
							else if(operador==p) Fmulti(numerador1,numerador2,denominador1,denominador2);
							else if(operador==d) Fdivi(numerador1,numerador2,denominador1,denominador2);
							else error=true;
						}
						else error=true;
					}
					else if(operador==e)FpotenG(numerador1,denominador1,denominador2,error,escrito);
					else if (operador==memo) {memoryN = numerador1; memoryD=denominador1;}
					else if(operador==smemo) {numerador1 = memoryN; denominador1 = memoryD;}
					else if(operador==simplificar) Fsimpli(numerador1, denominador1, MCD);		
					else if (operador==cancel) 
					{ 
						system("cls"); 
						numerador1 = 0;
						denominador1=1; 
						escrito << endl << "Borrar"; 
					}
					else if((operador != s)&&(operador != y)&&(operador != p)&&(operador != d)&&(operador != e)&&(operador != simplificar)&&(operador != cancel)&&(operador != salir)) 
					error = true;

					cin.get(operador);
					escrito << operador << flush;
				}
				erroresCalculadoraMfracciones(numerador1,denominador1,error,escrito);
				error = false;
			}
		}while(fin == false);
		cin.clear(); 
		system("CLS");
		cin.sync();
	}
	void FprimerCaracter(int &numerador1,int &denominador1, char &operador, char &salir, bool &error,bool &fin, ofstream &escrito,char y,char s,char separador,char &cancel,char p,char d,char e,char simplificar,char memo, char smemo,int &memoryN,int &memoryD)
{
			char operando;
			operador = cin.peek(); // Se mira primer caracter y en funcion de lo que sea:
			if (operador == salir) 
			{ 
				fin = true;  //Salir al menu
				escrito << endl << operador << endl << flush; 
				escrito << endl <<"Salir al menu "<<endl << "-----------------------------------" << endl << endl << flush;
			} 	
			else if (operador >= '0' && operador <= '9')
			{ 
				cin >> numerador1; // Operación normal 
				escrito << numerador1 << flush;
				operador = cin.peek();
					if (operador == '|')
					{
						cin.get(separador);
						escrito << separador << flush;
						operando=cin.peek();
						if ((operando >= '0' && operando <= '9'))
						{
						cin >> denominador1;
						escrito << denominador1 << flush;
						cin.get(operador);
						escrito << operador << flush;
						}else error=true;
					}
					else if (operador == s || operador == y || operador == p || operador == d || operador==e || operador==simplificar) 
					{
					cin.get(operador);
					denominador1=1;
					escrito << operador << flush;
					}
					else error = true;
			}
			else if (operador == smemo) // Guardar como numerador1 y denominador1 el valor de la memoria
			{ 
				numerador1 = memoryN;
				denominador1 = memoryD;
				cin.get(operador);
				escrito << operador << flush;
			} 
			else 
			{ 
				cin.get(operador);
				escrito << operador << flush; 
			}
				error = cin.fail() ; // Error si se introduce un caracter extraño
}
	void mcd(int denominador1, int denominador2, int &MCD)
{
		int aux;

		while(denominador2 != 0)
		{
		aux = denominador2;
		denominador2 = denominador1 % denominador2;
		denominador1 = aux;
		MCD= denominador1;
		}
		
}
	void mcm(int denominador1, int denominador2, int &MCM, int MCD)
{
	mcd(denominador1,denominador2,MCD);
	MCM= (denominador1 * denominador2)/MCD;
}
	void Fsuma(int &numerador1,int numerador2,int &denominador1, int denominador2, int MCM, int MCD)
{
	if(denominador2 == denominador1)
		numerador1=numerador1+numerador2;			
	else if (denominador1 != denominador2)
	{
			mcm(denominador1,denominador2,MCM,MCD);
			numerador1=((MCM/denominador1)*numerador1)+((MCM/denominador2)*numerador2);
			denominador1=MCM;
	}
}
	void Fresta(int &numerador1,int numerador2,int &denominador1, int denominador2, int MCM, int MCD)
{
	if(denominador2 == denominador1)
		numerador1=numerador1-numerador2;			
	else if (denominador1 != denominador2)
	{
			mcm(denominador1,denominador2,MCM,MCD);
			numerador1=((MCM/denominador1)*numerador1)-((MCM/denominador2)*numerador2);
			denominador1=MCM;
	}
}
	void Fmulti(int &numerador1,int numerador2,int &denominador1, int denominador2)
{
	if(numerador2== -1)numerador1= numerador1 * -1;
	else
	{
	numerador1=numerador1*numerador2;
	denominador1=denominador1*denominador2;
	}
}
	void Fdivi(int &numerador1,int numerador2,int &denominador1, int denominador2)
{
	numerador1=numerador1*denominador2;
	denominador1=denominador1*numerador2;
}
	void FpotenG(int &numerador1,int &denominador1, int denominador2,bool &error,ofstream &escrito)
	{		
		int auxP;
		double numerador2;
		char operando;

		operando=cin.peek();
		if ((operando >= '0' && operando <= '9'))
		{
			error=cin.fail();
			cin >> numerador2;
			escrito << numerador2 << flush;
				if (numerador2 - floor(numerador2) != 0)
				{
					error =true;
					cout << "El exponente tiene que ser entero" << endl;
					escrito << endl << "El exponente tiene que ser entero" << flush;
				}
				else 
				{
				denominador2=1;	
				auxP=numerador1;
				FpotenN(numerador1,numerador2,denominador1,denominador2,error, escrito);
				FpotenD(auxP,numerador2,denominador1,denominador2,error,escrito);
				}
		}else if(operando=='-')
		{
			cin.get(operando);//se coge el signo para verificar si hay un caracter extraño
			operando=cin.peek();
			if ((operando >= '0' && operando <= '9'))
			{
			error=cin.fail();
			cin >> numerador2;
			escrito << numerador2 << flush;
				if (numerador2 - floor(numerador2) != 0)
				{
					error =true;
					cout << "El exponente tiene que ser entero" << endl;
					escrito << endl << "El exponente tiene que ser entero" << flush;
				}
				else 
				{
				denominador2=1;	
				auxP=numerador1;
				numerador2= numerador2*-1;//se recupera el signo del numero
				FpotenN(numerador1,numerador2,denominador1,denominador2,error, escrito);
				FpotenD(auxP,numerador2,denominador1,denominador2,error,escrito);
				}
			}
		}else error=true;			
	}
	void FpotenN(int &numerador1,double numerador2,int denominador1, int denominador2,bool &error,ofstream &escrito)
	{	  
		int exponencial;
	  
		if (numerador2 == 0) numerador1 = 1;
		else if (numerador2 == 1) numerador1 = numerador1;			
		else if (numerador2 == -1) numerador1 = denominador1;											 
		else if (numerador2 >= 2) 
		{
			exponencial = numerador1;				
			while (numerador2 > 1)
			{
				numerador1 = numerador1 * exponencial;
				numerador2 = numerador2 -1;
			}
		}
		else if (numerador2 <= -2) 
		{ 
			numerador1 = denominador1;
			exponencial = numerador1;
			while (numerador2 <= -2) 
			{
				numerador1 = numerador1 * exponencial;
				numerador2 = numerador2 + 1;
			} 
		} else error = true; 		
	}
	void FpotenD(int auxP,double numerador2,int &denominador1, int denominador2,bool &error,ofstream &escrito)
	{
	 int exponencial;  
	 
			if (numerador2 == 0) denominador1 = 1;
			else if (numerador2 == 1) denominador1 = denominador1;
			else if (numerador2 == -1) denominador1 = auxP; 
			else if (numerador2 >= 2) 
			{
				exponencial = denominador1;				
				while (numerador2 > 1)
				{
					denominador1 = denominador1 * exponencial;
					numerador2 = numerador2 -1;
				}
			}
			else if (numerador2 <= -2) 
			{ 
				denominador1 = auxP;
				exponencial = denominador1;
				while (numerador2 <= -2) 
				{
					denominador1 = denominador1 * exponencial;
					numerador2 = numerador2 + 1;
				} 
			} else error = true; 
	}
	void Fsimpli(int &numerador1,int &denominador1, int MCD)
	{
		mcd(numerador1, denominador1,MCD);
		numerador1=numerador1/MCD;
		denominador1=denominador1/MCD;
	}
	void configuracion(char &s, char &y, char &p, char &d, char &e, char &f, char &z, char &cancel, char &salir, char &memo, char &smemo, char &simplificar)
	{
		char opcionConf, operador, enter = '\n';
		bool salida = false;
		
		do 
		{	cout << "Introduzca la eleccion que quiere: " << endl;
			cout << "-----------------------------------" << endl << endl;
			cout << "Operadores actualmente en uso: " << s << " " << y << " " << p << " " << d << " " << e << " " << f << " " << z << " " << cancel << " " << salir << " " << memo << " " << smemo << " " << simplificar << endl << endl; 
			
			configuracionMenu(opcionConf, enter);
			if(salida == false)
			{
				if((opcionConf == 'a')&&(enter == '\n')){ operador = s; cambioConf(operador); s = operador; } 
				else if((opcionConf == 'b')&&(enter == '\n')){ operador = y; cambioConf(operador); y = operador; }
				else if((opcionConf == 'c')&&(enter == '\n')){ operador = p; cambioConf(operador); p = operador; }
				else if((opcionConf == 'd')&&(enter == '\n')){ operador = d; cambioConf(operador);  d = operador;}
				else if((opcionConf == 'e')&&(enter == '\n')){ operador = f; cambioConf(operador); f = operador; }
				else if((opcionConf == 'f')&&(enter == '\n')){ operador = e; cambioConf(operador); e = operador;}
				else if((opcionConf == 'g')&&(enter == '\n')){ operador = z; cambioConf(operador); z = operador; }
				else if((opcionConf == 'h')&&(enter == '\n')){ operador = cancel; cambioConf(operador); cancel = operador; }
				else if((opcionConf == 'i')&&(enter == '\n')){ operador = salir; cambioConf(operador); salir = operador; }
				else if((opcionConf == 'j')&&(enter == '\n')){ operador = memo; cambioConf(operador); memo = operador; }
				else if((opcionConf == 'k')&&(enter == '\n')){ operador = smemo; cambioConf(operador); smemo = operador; }
				else if((opcionConf == 'l')&&(enter == '\n')){ operador = simplificar; cambioConf(operador); simplificar = operador; }
				else if((opcionConf == 'm')&&(enter == '\n')){system("CLS");s = '+'; y = '-'; p = '*'; d = '/'; e = '^'; f = '!'; z = 'r'; cancel = 'c'; salir = 'x'; memo = 'm'; smemo = 'n';simplificar = 's';}
				else if((opcionConf == 'n')&&(enter == '\n')) salida = true;
				else
				{
					system("CLS");
					if((opcionConf < 'a')||(opcionConf > 'n')||(enter != '\n'))
					cout << "ERROR!! Introduce un valor valido" << endl;
				}	
				
			}	
		}while((opcionConf < 'a')||(opcionConf > 'n')||(salida == false));

		ofstream conf("conf.txt"); //se genera un archivo conf.txt siempre que se sale de la configuracion (se haya cambiado algo o no)
		conf << s << y << p << d << e << f << z << cancel << salir << memo << smemo << simplificar;
		conf.close();
		system("CLS");
	}
	void configuracionMenu(char &opcionConf, char &enter) //texto mostrado en pantalla de la configuracion y eleccion del menu
	{
				
			cout << " a) Configuracion del operador Suma " << endl;
			cout << " b) Configuracion del operador Resta " << endl;
			cout << " c) Configuracion del operador Multiplicacion " << endl;
			cout << " d) Configuracion del operador Division " << endl;
			cout << " e) Configuracion del operador Factorial " << endl;
			cout << " f) Configuracion del operador Exponencial " << endl;
			cout << " g) Configuracion del operador Raiz Cuadrada " << endl;
			cout << " h) Configuracion del operador Cancelr " << endl;
			cout << " i) Configuracion del operador Salir " << endl;
			cout << " j) Configuracion del operador Guardar en Memoria " << endl;
			cout << " k) Configuracion del operador Sacar de Memoria " << endl;
			cout << " l) Configuracion del operador Simplificar(Solo en Modo fracciones) " << endl;
			cout << " m) Restablece a valores predeterminados " << endl;
			cout << " n) Salir al menu principal " << endl;
			
			cout << " " << endl;
			cout << "Porfavor, no asigne un mismo operador a dos operaciones distintas " << endl;
			cout << "Porfavor, no asigne un numero a un operador " << endl << endl;

			cin >> opcionConf;
			cin.get(enter);
			cin.sync();
	}	 
	char cambioConf(char &operador) //funcion que cambia el operador de una operacion
	{
		char noperador;

		system("CLS");
		cout << "El operador actual es " << operador << endl << "Introduzca el nuevo: ";
		noperador = cin.get(); 
		cin.sync();
		if(noperador != '\n') operador = noperador; //cambiar operador por el introducidoo
		system("CLS");

		return operador;
	}

	