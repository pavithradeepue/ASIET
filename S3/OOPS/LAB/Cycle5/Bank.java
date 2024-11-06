/* Pavithra Deepu E
S3 CSE-AI 47
Program to show Thread Synchronization */

class SavingsAccount {
    private int funds = 1000;

    public synchronized void addFunds(int amount) {
        funds += amount;
        System.out.println(Thread.currentThread().getName() + " Deposited amount: " + amount + ", New Balance: " + funds);
    }

    public synchronized void withdrawFunds(int amount) {
        if (funds >= amount) {
            funds -= amount;
            System.out.println(Thread.currentThread().getName() + " Withdrawn amount: " + amount + ", New Balance: " + funds);
        } else {
            System.out.println(Thread.currentThread().getName() + " tried to withdraw: " + amount + " but insufficient funds. Balance: " + funds);
        }
    }

    public int getFunds() {
        return funds;
    }
}

class Customer extends Thread {
    private SavingsAccount account;

    public Customer(SavingsAccount account) {
        this.account = account;
    }

    public void run() {
        for (int i = 0; i < 3; i++) {
            account.addFunds(100);
            account.withdrawFunds(200);
        }
    }
}

class Bank {
    public static void main(String[] args) {
        SavingsAccount sharedAccount = new SavingsAccount();
        Customer customer1 = new Customer(sharedAccount);
        Customer customer2 = new Customer(sharedAccount);
        
        customer1.setName("Customer 1");
        customer2.setName("Customer 2");
        
        customer1.start();
        customer2.start();
    }
}
