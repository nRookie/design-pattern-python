public class Singleton {
    private volatile static Singleton uniqueInstance;

    private Singleton() {}

    public static synchronized Singleton getInstance(){
        if(uniqueInstance == null) {
            //Check for an instance and if there isn't one , enter a synchronized block.
            synchronized(Singleton.class) {
                if(uniqueInstance == null){
                    uniqueInstance = new Singleton();
                }
            }
        }
        return uniqueInstance;
    }

    // other useful methods here
}

/*
The volatile keyword ensures that multiple threads handle the uniqueInstance variable
correctly when it is being initialized to the Singleton instance.
*/