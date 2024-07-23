import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String[] favoriteWords = new String[5];

        System.out.println("Please enter your 5 favorite words:");
        for (int i = 0; i < 5; i++) {
            favoriteWords[i] = scanner.nextLine();
        }

        for (String word : favoriteWords) {
            for (int i = 0; i < 5; i++) {
                new WordThread(word).start();
            }
        }
    }
}
