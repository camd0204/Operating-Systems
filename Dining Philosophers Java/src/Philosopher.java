import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Lock;

public class Philosopher extends Thread {

    private int index;
    private String state;
    private Philosopher leftPhilosopher;
    private Philosopher rightPhilosopher;
    private int timesEating;
    private Lock tableLock;
    private Semaphore privateLock;

    private static String THINKING = "[?] THINKING";
    private static String EATING = "[+] EATING";
    private static String HUNGRY = "[-] HUNGRY";


    public Philosopher(int index,Lock tableLock) {
        this.index = index;
        this.state = THINKING;
        this.timesEating = 0;
        this.tableLock = tableLock;
        this.privateLock = new Semaphore(1);
    }

    // SETTERS / GETTERS

    public void setRightPhilosopher(Philosopher rightPhilosopher){
        this.rightPhilosopher=rightPhilosopher;
    }

    public void setLeftPhilosopher(Philosopher leftPhilosopher){
        this.leftPhilosopher=leftPhilosopher;
    }

    public void setID(int id){
        this.index=id;
    }
    public int getID(){
        return this.index;
    }
    public void setPState(String state){
        this.state=state;
    }
    public String getPState(){
        return this.state;
    }

    // TO STRING / PRINT

    @Override
    public String toString(){
        return String.format("[Philosopher] Index: %d - State: %s - Times Eating: %d\n", 
         this.index  , this.getPState(), this.timesEating);
    }

    public void printState(){
        System.out.printf("Philosopher %d --> %s\n", this.index, this.getPState());
    }

    // SYNCHRONIZATION
    
    public void run(){
        try {
            this.privateLock.acquire();
            while (true){
                this.think();
                this.takeForks(tableLock);
                this.eat();
                this.putForks(tableLock);
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void think() throws InterruptedException{
        this.setPState(THINKING);
        this.printState();
        Thread.sleep((long) (1 + 2*Math.random()) * 1000);
    }

    public void  takeForks(Lock tableLock) throws InterruptedException{
        tableLock.lock();
        this.setPState(HUNGRY);
        this.testForks();
        tableLock.unlock();
        this.privateLock.acquire();  
    }

    public void testForks() throws InterruptedException{
        if(this.getPState()==HUNGRY && this.leftPhilosopher.getPState()!=EATING && this.rightPhilosopher.getPState()!=EATING){
            this.setPState(EATING);
            this.privateLock.release();;
        }
    }

    public  void putForks(Lock tableLock) throws InterruptedException{
        tableLock.lock();
        this.setPState(THINKING);
        this.leftPhilosopher.testForks();
        this.rightPhilosopher.testForks();
        tableLock.unlock();
    }

    public  void eat() throws InterruptedException{
        this.timesEating+=1;
        this.printState();
        DiningTable.printTableInfo();
        Thread.sleep((long) (2+ 3*Math.random()) * 1000);
    }
    
}
