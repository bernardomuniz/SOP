//Em Java, o Mutex é implementado pela classe ReentrantLock. Ele funciona exatamente
//como o pthread_mutex_t do C: você precisa dar o lock() manualmente e, obrigatoriamente, o unlock().
//Exemplo m8-mutex.c




package exemplo1.mutex;
import java.util.concurrent.locks.ReentrantLock;



public class Mutex{
    public static final int NUM_THREADS = 100;
    public static final int NUM_STEPS = 100000;
    private static int sum = 0;
    private static final ReentrantLock lock = new ReentrantLock();

    static void threadBody(int id){
        long my_id = (long)id;

        for ( int i = 0; i < NUM_STEPS; i++){
            lock.lock();

            try {
                sum += 1;
                if (sum % 100000 == 0){
                System.out.println("Thread " + my_id + " incrementou. Sum: " + sum);
                }
            } finally {
                lock.unlock();
            }
            
        }
    }

    public static void main(String[] args) {
        Thread[] threads = new Thread[NUM_THREADS];
        long expected = (long)NUM_THREADS * NUM_STEPS;
        
        for (int i = 0; i < NUM_THREADS; i++) {
            int id = i;
            threads[i] = new Thread(() -> threadBody(id));
            threads[i].start();
        }

        for (int i = 0; i < NUM_THREADS; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
        
        System.out.println("\n--- Resultado: Pthread Mutex ---");
        System.out.println("Valor esperado: " + expected);
        System.out.println("Valor obtido: " + sum);
        System.out.println("Diferença: " + (expected-sum));

    }


}
