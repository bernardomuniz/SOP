package ex2.mutex;
import java.util.concurrent.locks.ReentrantLock;

class ContaMutex {
private float saldo = 0;
private static final ReentrantLock lock = new ReentrantLock();


public synchronized void depositar (float valor) {
    lock.lock();

    try {
        if (valor >= 0)
            saldo += valor ;
        else
            System.err.println("valor negativo");
        
    } finally {
        lock.unlock();
    }

    
}
public synchronized void retirar (float valor){
    lock.lock();

    try{
        if (valor >= 0)
            saldo -= valor ;
        else
            System.err.println("valor negativo");
    }finally{
        lock.unlock();
    }
}

public static void main(String[] args) {

}


}