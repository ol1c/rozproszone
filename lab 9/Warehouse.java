package org.example;

import java.util.*;

class Warehouse {
    private final int capacity;
    private int currentSize = 0;
    private final Map<String, Integer> storage = new HashMap<>();
    private final String[] productTypes = {"Mleko", "Mąka", "Kakao"};

    public Warehouse(int capacity) {
        this.capacity = capacity;
    }

    public synchronized void produce(String type, int amount) throws InterruptedException {
        while (currentSize + amount > capacity) {
            wait();
        }
        storage.put(type, storage.getOrDefault(type, 0) + amount);
        currentSize += amount;
        System.out.println("Producent wyprodukował " + amount + " szt. typu " + type);
        notifyAll();
    }

    public synchronized int consume(String type, int requestedAmount) throws InterruptedException {
        while (!storage.containsKey(type) || storage.get(type) == 0) {
            wait();
        }
        int available = storage.get(type);
        int taken = Math.min(requestedAmount, available);
        storage.put(type, available - taken);
        currentSize -= taken;
        System.out.println("Konsument kupił " + taken + " szt. typu " + type);
        notifyAll();
        return taken;
    }

    public synchronized void printStatus() {
        System.out.println("Stan magazynu: " + storage + ", zajętość: " + currentSize + "/" + capacity);
    }

    public String[] getProductTypes() { return this.productTypes; }
}