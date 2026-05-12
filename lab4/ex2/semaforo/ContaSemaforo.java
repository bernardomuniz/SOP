package ex2.semaforo;

import java.util.concurrent.Semaphore;

class ContaSemaforo {
private float saldo = 0;
private static final Semaphore semaforo = new Semaphore(2);

public synchronized void depositar (float valor) {

    try {
        semaforo.acquire();
        if (valor >= 0)
            saldo += valor ;
        else
            System.err.println("valor negativo");
        
    }catch (InterruptedException e){
        Thread.currentThread().interrupt();
    }finally{
        semaforo.release();
    }
   
}
public synchronized void retirar (float valor){

    try {
        semaforo.acquire();
        if (valor >= 0)
            saldo -= valor ;
        else
            System.err.println("valor negativo");

    }catch (InterruptedException e){
        Thread.currentThread().interrupt();
    }finally{
        semaforo.release();
    }   
}
}