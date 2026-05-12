package exemplo3.Monitor;

import java.util.LinkedList;
import java.util.Queue;


class Mesa {
    private String pizza;
    //private boolean mesaVazia = true;
    public static Queue<String> pizzas = new LinkedList<>(); //a fila de pizzas começa vazia
    

    // Monitor: Garante que só um mexe na mesa por vez
    public synchronized void colocarPizza(String nomePizza) throws InterruptedException {
        //se a fila de pizzas consegue armazenar 2 pizzas, o cozinheiro continua colocando pizzas, se não, ele espera
        while (pizzas.size() == 2) {
            System.out.println("-> Mesa cheia! Cozinheiro esperando...");
            wait();
        }

        pizzas.add(nomePizza);

        System.out.println("Cozinheiro colocou a pizza de: " + pizzas);
        // Avisa o entregador que tem pizza pronta
        notifyAll();
    }

    public synchronized String retirarPizza() throws InterruptedException {
        // Se a fila de pizzas estiver vazia, o entregador dorme e solta o lock
        while (pizzas.isEmpty()) {
            System.out.println("-> Mesa vazia! Entregador esperando...");
            wait();
        }

        String p = pizzas.poll();
        System.out.println("Entregador levou a pizza de: " + p);
        // Avisa o cozinheiro que a mesa liberou
        notifyAll();
        return p;
    }
}