// O Java utiliza a classe Semaphore. Você define o número de "permissões"(vagas) no
//construtor.
//Implementação do estacionamento.c

package exemplo1.semaforo;
import java.util.Random;
import java.util.concurrent.Semaphore;


public class Semaforo {
    public static final int TOTAL_VAGAS = 5;
    public static final int TOTAL_CARROS = 10;

    private static final Semaphore semaforo = new Semaphore(TOTAL_VAGAS);
    private static final Random r = new Random();

    static void entrar_no_estacionamento(int arg){
        System.out.println("Carro " + arg + " chegou e está procurando vaga...");
        
            
        
        try{
            semaforo.acquire(); //Se não houver vaga, o semáforo bloqueia aqui

            System.out.println("--> Carro " + arg + " ENTROU.");

            Thread.sleep(5000 + (r.nextInt(3000)));
        }catch (InterruptedException e){
            Thread.currentThread().interrupt();
        }finally{
            System.out.println("<-- Carro " + arg + " SAIU. Liberando vaga...");
            semaforo.release();
        }

    }
    public static void main(String[] args) {
         Thread[] threads = new Thread[TOTAL_CARROS];
        
        for (int i = 0; i < TOTAL_CARROS; i++) {
            int id = i + 1;
            threads[i] = new Thread(() -> entrar_no_estacionamento(id));
            try {
                Thread.sleep(600); 
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            threads[i].start();
            
        }

        for (int i = 0; i < TOTAL_CARROS; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }

        System.out.println("\nEstacionamento encerrado.\n");
    }

}
