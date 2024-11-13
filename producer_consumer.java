import java.lang.Runnable;
import java.lang.Thread;
import java.util.concurrent.Semaphore;
import java.util.Vector;

class Container
{
    Vector<Integer> buffer=new Vector<>(10);
    static final int buffersize=10;

    Semaphore con=new Semaphore(0);
    Semaphore prod=new Semaphore(1);
    Semaphore empty_slots=new Semaphore(buffersize);

    void put(int item)
    {
        try
        {
            prod.acquire();
            empty_slots.acquire();
            
            buffer.add(item);
            System.out.println("Producer produced item"+item);
            System.out.println("No. of items produced: "+buffer.size());
            System.out.println("No. of items producer can produce: "+empty_slots.availablePermits());
            
            con.release();
            prod.release();
        }
        catch(InterruptedException e)
        {
            System.out.println(e);
        }
    }
    void get()
    {
        try
        {
            prod.acquire();
            con.acquire();

            if(buffer.size()>0)
            {
                int item=buffer.remove(0);
                System.out.println("Item consumed: "+item);
                System.out.println("Cunsumer can still consume: "+buffer.size());
            }
            empty_slots.release();
            prod.release();
        }
        catch(InterruptedException e)
        {
            System.out.println(e);
        }
    }
}

class Producer implements Runnable
{
    Container c;
    Producer(Container c)
    {
        this.c=c;
        new Thread(this,"Producer").start();
    }
    public void run()
    {
        try
        {
            for(int i=1;i<=10;i++)
            {
                c.put(i);
                Thread.sleep(3);
            }
        }
        catch(InterruptedException e)
        {
            System.out.println(e);
        }
    }
}
class Consumer implements Runnable
{
    Container c;
    Consumer(Container c)
    {
        this.c=c;
        new Thread(this,"Consumer").start();
    }
    public void run()
    {
        try
        {
            for(int i=1;i<=10;i++)
            {
                c.get();
                Thread.sleep(3);
            }
        }
        catch(InterruptedException e)
        {
            System.out.println(e);
        }
    }
}

class producer_consumer
{
    public static void main(String args[])
    {
        Container c=new Container();
        new Producer(c);
        new Consumer(c);
    }
}