public class WordThread extends Thread {
    private String word;

    public WordThread(String word) {
        this.word = word;
    }

    @Override
    public void run() {
        try {
            Thread.sleep(1000);
            char firstChar = word.toLowerCase().charAt(0);
            String[] prePostWords = ConfigSingleton.getInstance().getPrePostWords(firstChar);
            String preWord = prePostWords[0];
            String postWord = prePostWords[1];
            System.out.println(preWord + " " + word + " " + postWord);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
