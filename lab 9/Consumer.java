package org.example;

import java.util.*;
import java.util.concurrent.*;

class Consumer extends Thread {
    private final Warehouse warehouse;
    private final Random rand = new Random();
    private final String[] productTypes;

    public Consumer(Warehouse warehouse) {
        this.warehouse = warehouse;
        this.productTypes = warehouse.getProductTypes();
    }

    public void run() {
        try {
            while (true) {
                String type = productTypes[rand.nextInt(productTypes.length)];
                int amount = rand.nextInt(1, 6);
                warehouse.consume(type, amount);
                warehouse.printStatus();
                Thread.sleep(TimeUnit.SECONDS. toMillis (rand.nextInt(3, 8)));
            }
        } catch (InterruptedException e) {
            System.out.println("Konsument zakończył działanie.");
        }
    }
}
