package exemplo3.Monitor;

public class Pizzaria {
    public static void main(String[] args) {
        Mesa mesa = new Mesa();
       
     
        // Thread do Cozinheiro
        new Thread(() -> {
            
            try {
                String[] cardapio = {"Calabresa", "Mussarela", "Portuguesa", "Marguerita", "Frango"};
                for (String p : cardapio) {
                    mesa.colocarPizza(p);
                    Thread.sleep(0); // Cozinheiro lento
                }
            } catch (InterruptedException e) {}
        }).start();

        // Thread do Entregador
        new Thread(() -> {
            try {
                for (int i = 0; i < 3; i++) {
                    mesa.retirarPizza();
                    Thread.sleep(3000); //Entregador rápido
                }
            } catch (InterruptedException e) {}
        }).start();
    }
}
