package org.example;

import java.util.*;
import java.util.concurrent.*;

class Producer extends Thread {
    private final Warehouse warehouse;
    private final Random rand = new Random();
    private final String[] productTypes;

    public Producer(Warehouse warehouse) {
        this.warehouse = warehouse;
        this.productTypes = warehouse.getProductTypes();
    }

    public void run() {
        try {
            while (true) {
                String type = productTypes[rand.nextInt(productTypes.length)];
                int amount = rand.nextInt(1, 6);
                warehouse.produce(type, amount);
                warehouse.printStatus();
                Thread.sleep(TimeUnit.SECONDS. toMillis (rand.nextInt(3, 8)));
            }
        } catch (InterruptedException e) {
            System.out.println("Producent zakończył działanie.");
        }
    }
}