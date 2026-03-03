/*
* Programa: currency_converter.cpp
* Objetivo: Motor de cambio de divisas con sesiones y
estadísticas
* Tema: Lazos estructurados, acumuladores, estadísticas en
tiempo real
* Autor: MARTIN ENRIQUEZ
* Fecha: 23/02/2026
* IA utilizada: SI, CHAT GPT, CONOCER EL ALMACENAMIENTO DE VARIABLES EN VECTORES
*
* Decisiones de diseño:
* - Inicialización de min con numeric_limits<double>::max()
* - Validación por fallas en la entrada de cin y manual
*/
#include <iostream>
#include <limits>
//libreria que detecta fallos en la funcion "cin", para facilitar validaciones
#include <iomanip>
//libreria para fijar solo dos decimales en los numeros.
#include <locale>
//libreria que usa la coma como separador de miles
#include <vector>
//libreria que me servirá posteriormente para almacenar valores en un vector, y despues imprimir
using namespace std;

int main(){
    string divisa_base="";
    string divisa_cotizada="";
    int modo;
    vector<string> historial_pares;//vectores y variables para guardar un historial general (extra)
    vector<double> historial_base;
    vector<double> historial_convertido;
    while(true){
        cout<<"Seleccione el modo: (1) Continua (2) Sesion (3) Salir: ";
        cin>>modo;
        if(modo==1){
            vector<string> pares;
            vector<double> tasas;
            vector<double> montos_base;
            vector<double> montos_convertidos;
            while (true) {
                cout<<"Ingrese un codigo para la divisa base (puede ingresar USD,EUR, JPY): \n";
                cin>>divisa_base;
                //[IA STARTED] por problemas de interpretacion de operadores (confundí las acciones del or con las del and), la validación no estaba funcionando
                if(divisa_base!= "USD" and divisa_base!= "EUR" and divisa_base!= "JPY"){ //[IA FINISHED]
                    cout<<"POR FAVOR INGRESE UNO DE LOS CODIGOS VALIDOS\n";
                    continue;//si el usuario ingresa un codigo no válido, vuelve a pedir el codigo de divsa
                }
                cout<<"Ingrese un codigo para la divisa cotizada (puede ingresar USD,EUR, JPY): \n";
                cin>>divisa_cotizada;
                //si el usuario ingresa un codigo no válido, vuelve a pedir el codigo de divsa
                if(divisa_cotizada!= "USD" and divisa_cotizada!= "EUR" and divisa_cotizada!= "JPY"){
                    cout<<"POR FAVOR INGRESE UNO DE LOS CODIGOS VALIDOS\n";
                    continue;
                }
                cout<<"USTED VA A TRANSFORMAR DE "<<divisa_base<<" A "<<divisa_cotizada;
                double tasa_cambio;
                cout<<"\nPOR FAVOR INGRESE LA TASA DE CAMBIO: ";
                cin>>tasa_cambio;
                //[IA STARTED] para detectar fallos en la funcion "cin", y  si hay un fallo pide al usuario ingresar nuevamente el dato hasta que no haya error
                while(cin.fail() or tasa_cambio<=0)//no se puede escribir un string en un double (no sabia) por eso la libreria #include <limits>
                {
                    cin.clear(); // limpia el estado de error
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // borra basura
                    
                    cout << "ENTRADA INVALIDA. INGRESE UNA TASA NUMERICA POSITIVA: ";
                    cin >> tasa_cambio;
                }//[IA FINISHED]
                double monto;
                cout<<"\nPOR FAVOR INGRESE EL MONTO INICIAL: ";
                cin>>monto;//[IA STARTED]
                while(cin.fail() or monto<=0)
                {
                    cin.clear(); // limpia el estado de error
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // borra basura [IA FINISHED]
                    
                    cout<<"POR FAVOR, INGRESE UN MONTO VALIDO (MAYOR A 0"<<"\nINGRESE NUEVAMENTE EL MONTO: ";
                    cin>>monto;
                    
                }
                double conversion;
                conversion=monto*tasa_cambio;//se hace la conversion normal
                //[IA STARTED]
                cout.imbue(locale("en_US.UTF-8"));//separar los miles con una coma
                cout<<"\nLA CONVERSION ES: "<<fixed<<setprecision(2)<<conversion;//poner solo dos decimales aproximados [IA END]
                
               //[ia started] almacenar los valores en los vectores
                pares.push_back(divisa_base + "/" + divisa_cotizada);
                tasas.push_back(tasa_cambio);
                montos_base.push_back(monto);
                montos_convertidos.push_back(conversion);//[ia finished]
                
                //vectores para guardar el historial general
                historial_pares.push_back(divisa_base + "/" + divisa_cotizada);
                historial_base.push_back(monto);
                historial_convertido.push_back(conversion);
                
                string salida="";
                
                cout<<"\nDESEA REALIZAR OTRA CONVERSION? (SI/NO)";
                //ahora se pregunta al usuario si desea continuar en el programa
                cin>>salida;
                if (salida == "No" or salida == "no" or salida == "NO"){//comparacion para acctivar la salida del programa
                    cout<<"\nHA SIDO UN GUSTO ATENDERLE, BUEN DIA!\n";
                    break;
                }
            }
            cout << "\nRegresando al menú principal...\n";

            for (int i = 0; i < pares.size(); i++) {//[ia started] lazo de repeticion para imprimir todas las conversiones

                cout << "\n=== CONVERSION DE DIVISAS ===\n";
                cout << "Par: " << pares[i];
                cout << "Tasa: " << fixed << setprecision(6) << tasas[i];//mostrar los decimales

                cout.imbue(locale("en_US.UTF-8"));//separador de miles

                cout << "Monto base: "
                     << fixed << setprecision(2)
                     << montos_base[i] << " "
                     << pares[i].substr(0,3) << endl;

                cout << "Monto convertido: "
                     << montos_convertidos[i] << " "
                     << pares[i].substr(4,3) << endl;
            }//[IA FINISHED]
        }
        else if (modo == 2) {
            
            while (true) {
                
                cout << "Ingrese un codigo para la divisa base (USD, EUR, JPY): \n";
                cin >> divisa_base;
                
                if (divisa_base != "USD" and divisa_base != "EUR" and divisa_base != "JPY") {
                    cout << "POR FAVOR INGRESE UNO DE LOS CODIGOS VALIDOS\n";
                    continue;
                }
                
                cout << "Ingrese un codigo para la divisa cotizada (USD, EUR, JPY): \n";
                cin >> divisa_cotizada;
                
                if (divisa_cotizada != "USD" and divisa_cotizada != "EUR" and divisa_cotizada != "JPY") {
                    cout << "POR FAVOR INGRESE UNO DE LOS CODIGOS VALIDOS\n";
                    continue;
                }
                
                double tasa_cambio;
                cout << "\nPOR FAVOR INGRESE LA TASA DE CAMBIO: ";
                cin >> tasa_cambio;
                
                while (cin.fail() or tasa_cambio <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\nENTRADA INVALIDA. INGRESE UNA TASA NUMERICA POSITIVA: ";
                    cin >> tasa_cambio;
                }
                
                // ===== Variables de sesión =====
                int contador = 0;
                double total_base = 0;
                double total_convertido = 0;
                double min = numeric_limits<double>::max();//inicar con el min en infinito
                double max = 0;
                
                vector<double> montos;
                vector<double> convertidos;
                
                cout << "\n=== SESION DE CONVERSION ===\n";
                cout << "Par: " << divisa_base << "/" << divisa_cotizada << endl;
                cout << "Tasa: " << fixed << setprecision(6) << tasa_cambio << endl;
                
                // ===== Ingreso de montos =====
                while (true) {
                    
                    string entrada;
                    cout << "\nIngrese monto (o 'q' para salir): ";
                    cin >> entrada;
                    
                    if (entrada == "q" || entrada == "Q") {
                        break;
                    }
                    
                    double monto;
                    
                    try {//[IA started] intenta hacer algo esperando un error
                        monto = stod(entrada);
                    }
                    catch (...) {//[ia] finished, ante cualquier error, envia un mensaje de error
                        cout << "Entrada invalida.\n";
                        continue;
                    }
                    
                    if (monto <= 0) {
                        cout << "El monto debe ser mayor a 0.\n";
                        continue;
                    }
                    
                    double convertido = monto * tasa_cambio;
                    
                    // [IA STARTED]Guardar en cada iteracion en vectores para imprimir despues
                    montos.push_back(monto);
                    convertidos.push_back(convertido);//[IA FINISHED]
                    
                    //se guardan y actualizan los datos de los vectores para el historial general
                    historial_pares.push_back(divisa_base + "/" + divisa_cotizada);
                    historial_base.push_back(monto);
                    historial_convertido.push_back(convertido);
                    
                    // Se van actualizando las estadísticas
                    contador++;
                    total_base += monto;
                    total_convertido += convertido;
                    
                    if (monto < min) min = monto;
                    if (monto > max) max = monto;
                }
                
                // ===== Mostrar reporte =====
                if (contador == 0) {
                    cout << "\nNo se realizaron conversiones.\n";
                    continue;
                }
                
                for (int i = 0; i < contador; i++) {
                    
                    double acumulado_base = 0;
                    double acumulado_convertido = 0;
                    
                    for (int j = 0; j <= i; j++) { //[IA STARTED] otro for para ir acumulando las bases y las conversiones por cada sesion
                        acumulado_base += montos[j];
                        acumulado_convertido += convertidos[j];//[ia finished]
                    }
                    
                    cout << "\nConversion #" << i + 1 << ":\n";
                    cout << "Monto base: " << fixed << setprecision(2)
                    << montos[i] << " " << divisa_base << endl;
                    
                    cout << "Monto convertido: "
                    << convertidos[i] << " " << divisa_cotizada << endl;
                    
                    cout << "--- Estadisticas de la sesion ---\n";
                    cout << "Total conversiones: " << i + 1 << endl;
                    cout << "Total base acumulado: " << acumulado_base << endl;
                    cout << "Total convertido acumulado: " << acumulado_convertido << endl;
                    cout << "Promedio por conversion: "
                    << acumulado_base / (i + 1) << endl;
                    cout << "Monto minimo: " << min << endl;
                    cout << "Monto maximo: " << max << endl;
                }
                break;//salir al 'menu' principal
            }
        }
        else if(modo==3){
            //[ia started] proceso para mostrar el historial en el programa
            if(!historial_convertido.empty()){

                int indice_max = 0;

                for(int i = 1; i < historial_convertido.size(); i++){
                    if(historial_convertido[i] > historial_convertido[indice_max]){
                        indice_max = i;
                    }
                }

                cout << "\n=== HISTORIAL GENERAL ===\n";
                cout << "Total de conversiones realizadas: "
                     << historial_convertido.size() << endl;

                cout << "\nConversion mas alta:\n";
                cout << "Par: " << historial_pares[indice_max] << endl;
                cout << "Monto base: " << fixed << setprecision(2)
                     << historial_base[indice_max] << endl;
                cout << "Monto convertido: "
                     << historial_convertido[indice_max] << endl;
            }//[ia end]
            cout<<"\nHA SIDO UN PLACER ATENDERLE! QUE TENGA UN BUEN DIA :)";
                break;
            }
            else if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Opcion invalida. Intente nuevamente:\n";
                continue;
            }
        }
}

