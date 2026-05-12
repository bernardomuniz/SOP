package exemplo2.monitor;

public class MonitorConta {
    public static int saldo = 100;

    static synchronized void depositar(int arg){
        int valor = arg;
        
        try {
            Thread.sleep(0);
            int temp = saldo;
            temp += valor;           // Passo 2: Soma
            saldo = temp;           // Passo 3: Escrita

        }catch (InterruptedException e){
            Thread.currentThread().interrupt();
        }
        
    }

    public static void main(String[] args) {
        int v1 = 50, v2 = 30;
        Thread t1 = new Thread(()-> depositar(v1));
        Thread t2 = new Thread(()-> depositar(v2));

        t1.start();
        t2.start();

        try {
            t1.join();
            t2.join();
        }catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
        
        System.out.println("Saldo final esperado: 180");
        System.out.println("Saldo final obtido: " + saldo);
       

    }
}
