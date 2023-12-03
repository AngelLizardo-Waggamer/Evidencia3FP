#include <iostream>
#include <string>
using namespace std;

/* Declaración de variables globales*/
int opt;
string accounts[5][2] = {{"123", "300.50"}, {"124", "1050.00"}, {"125", "250.00"}, {"126", "4500.67"}, {"127", "1900.56"}};

/* Funciones */
void showMenu(); /* Muestra el menu principal*/
int findAccount(string account); /* Validar que la cuenta existe en el array de cuentas*/

int main(){

    cout<<"Bienvenido a cajeros pato.\n";

    /* Ciclo para que no se salga al terminar las operaciones */
    do
    {
        string tempAcc;  /* variable temporal para input de cuenta */
        int tempAccInd; /* Variable para guardar el index de la cuenta en el array de cuentas */
        string tempMoneyInput; /* Variable para guardar inputs de dinero */
        double accBalance; /* Variable para temporalmente almacenar el balance de una cuenta */
        showMenu();
        cout<<"Operacion: ";
        cin>>opt;

        switch (opt)
        {
        /* Caso de Consulta de Saldo */
            case 1:{
                cout<<"Ingrese su cuenta: ";
                cin>>tempAcc;
                tempAccInd = findAccount(tempAcc);

                if(tempAccInd != -1){ /* La respuesta estandar para cuentas que no existen es -1 */
                    cout<<"El saldo para la cuenta "<<accounts[tempAccInd][0]<<" es de $"<<accounts[tempAccInd][1];
                }else{
                    cout<<"La cuenta no es valida, vuelva a intentarlo";
                }
                break;
            }

        /* Caso de Retiro */
            case 2:{
                double moneyForRet;
                cout<<"Ingrese su cuenta: ";
                cin>>tempAcc;
                tempAccInd = findAccount(tempAcc);

                if(tempAccInd != -1) { /* El valor predeterminado para cuando no se encuentra una cuenta es -1*/
                    cout<<"Ingrese la cantidad de dinero a retirar: ";
                    cin>>tempMoneyInput;
                    moneyForRet = stod(tempMoneyInput); /* Convertir el input de dinero a double */
                    accBalance = stod(accounts[tempAccInd][1]); /* Convertir el balance de la cuenta a double para trabajarlo */

                    if(moneyForRet > accBalance){ /* Validar que el saldo es suficiente para concretar la operacion*/
                        cout<<"No posee del suficiente saldo para retirar esta cantidad. Vuelva a intentarlo.";
                    }else{
                        accounts[tempAccInd][1] = to_string(accBalance - moneyForRet); /* Guardar el nuevo balance en el array de cuentas */
                        cout<<"Operacion exitosa. Saldo restante: $"<<accounts[tempAccInd][1]<<". No olvide tomar su efectivo.";
                        accBalance = 0; /* Resetear la variable por seguridad*/
                    }


                }else{
                    cout<<"La cuenta no es valida, vuelva a intentarlo\n";
                }

                break;
            }
        
        /* Caso de Deposito */
            case 3:{
                double moneyForDeposit;
                cout<<"Ingrese su cuenta: ";
                cin>>tempAcc;
                tempAccInd = findAccount(tempAcc);

                if(tempAccInd != -1){
                    cout<<"Ingrese la cantidad a depositar: ";
                    cin>>tempMoneyInput;
                    moneyForDeposit = stod(tempMoneyInput); /* Convertir el dinero a double */
                    accBalance = stod(accounts[tempAccInd][1]); /* Almacenar el balance de la cuenta para trabajar con el */
                    accounts[tempAccInd][1] = to_string(accBalance + moneyForDeposit); /* Guardar el nuevo balance en el array */

                    cout<<"La operacion fue exitosa. Su nuevo saldo es de $"<<accounts[tempAccInd][1]<<".";
                    accBalance = 0; /* Resetear la variable por seguridad */
                }else{
                    cout<<"La cuenta no es valida, vuelva a intentarlo\n";
                }

                break;
            }
        /* Caso de transferencia */
            case 4:{
                int destAccInd; /* Index de cuenta destino */
                double destAccBal; /* Balance de cuenta destino */
                double moneyToTransf; /* Dinero a transferir */
                cout<<"Ingrese la cuenta de origen: ";
                cin>>tempAcc;
                tempAccInd = findAccount(tempAcc);

                if(tempAccInd != -1){
                    cout<<"Ingrese la cuenta destino: ";
                    cin>>tempAcc;
                    destAccInd = findAccount(tempAcc); /* Encontrar la cuenta destino */
                    if(destAccInd != -1){
                        cout<<"Ingrese la cantidad de dinero a transferir: ";
                        cin>>tempMoneyInput;
                        moneyToTransf = stod(tempMoneyInput); /* Convertir el dinero input a double */
                        accBalance = stod(accounts[tempAccInd][1]); /* Balance de cuenta origen */
                        destAccBal = stod(accounts[destAccInd][1]); /* Balance de cuenta destino */

                        accounts[tempAccInd][1] = to_string(accBalance - moneyToTransf); /* Restar el dinero de la cuenta origen*/
                        accounts[destAccInd][1] = to_string(destAccBal + moneyToTransf); /* Sumar el dinero a la cuenta destino*/
                        accBalance = 0; /* Reseteo a la variable por seguridad */
                        destAccBal = 0; /* Reseteo a la variable por seguridad*/

                        cout<<"Operacion exitosa. Saldo restante: $"<<accounts[tempAccInd][1];
                    }else{
                        cout<<"La cuenta destino no es valida, vuelva a intentarlo\n";
                    }
                }else{
                    cout<<"La cuenta no es valida, vuelva a intentarlo\n";
                }
                break;
            }

        /* Caso de salida */
            case 5:{
                cout<<"Gracias por usar cajeros pato. ¡Hasta la proxima!";
                break;
            }
            default:
                cout<<"Ingrese una operacion valida.";
                break;
        }

    } while (opt != 5);
    
    return 0;
}

void showMenu() {
    cout<<"\n--------------------------------------";
    cout<<"\nIngrese la operacion a realizar:\n";
    cout<<"1. Consulta de saldo\n";
    cout<<"2. Retiro\n";
    cout<<"3. Depósito\n";
    cout<<"4. Transferencia\n";
    cout<<"5. Salir\n";
}
int findAccount(string account) {
    int response = -1; /* Respuesta estandar para cuando no se encuentre la cuenta */
    for (int accIndex = 0; accIndex < 5; accIndex++){ /* 5 es el tamaño del array de cuentas */
        if (account == accounts[accIndex][0]){
            response = accIndex; /* Se le asigna a la variable de respuesta el index para devolverlo al finalizar de ejecutarse la funcion*/
        }
    }
    return response;
}
