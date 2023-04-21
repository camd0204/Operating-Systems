import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class DiningTable {
    private static int numPhilosophers=5;
    private static  Philosopher[] philosophers = new Philosopher[numPhilosophers];
    public static void main(String[] args) throws Exception {
        Lock tableLock=new ReentrantLock();
        for(int i=0;i<numPhilosophers;i++){
            Philosopher p=new Philosopher(i, tableLock);
            philosophers[i]=p;
        }
        for(int i=0;i<numPhilosophers;i++){
            philosophers[i].setLeftPhilosopher(philosophers[(i+numPhilosophers-1)%numPhilosophers]);
            philosophers[i].setRightPhilosopher(philosophers[(i+1)%numPhilosophers]);
        }
        for(int i=0;i<numPhilosophers;i++){
            philosophers[i].start();
        }
    }
    
    public static void printTableInfo(){
        String info = "\n";
        for(int i=0;i<numPhilosophers;i++){
            info += DiningTable.philosophers[i].toString();
        }
        System.out.println(info);
    }
}
