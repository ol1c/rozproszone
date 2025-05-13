package org.example;

public class Main {
    public static void main(String[] args) {
        Warehouse warehouse = new Warehouse(20);
        for (int i = 0; i < 3; i++) {
            new Producer(warehouse).start();
        }
        for (int i = 0; i < 2; i++) {
            new Consumer(warehouse).start();
        }
    }
}
