import java.io.*;
import java.util.HashMap;
import java.util.Map;

public class User {
    private static final String FILENAME = "user.txt";
    private Map<String, Integer> stats;

    public User() {
        stats = new HashMap<>();
    }

    public void load() {
        try (BufferedReader br = new BufferedReader(new FileReader(FILENAME))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] parts = line.split(" ");
                stats.put(parts[0], Integer.parseInt(parts[1]));
            }
            System.out.println("Loaded stats from file.");
        } catch (IOException e) {
            System.err.println("Failed to open file for reading.");
        }
    }

    public void save() {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(FILENAME))) {
            for (Map.Entry<String, Integer> entry : stats.entrySet()) {
                bw.write(entry.getKey() + " " + entry.getValue());
                bw.newLine();
            }
            System.out.println("Saved stats to file.");
        } catch (IOException e) {
            System.err.println("Failed to open file for writing.");
        }
    }

    public void reset(String name) {
        if (name.equals("bread")) {
            stats.clear();
            System.out.println("All history cleared.");
        } else {
            stats.remove(name);
            System.out.println("Statistics reset for " + name + ".");
        }
    }

    public void greet(String name) {
        if (!stats.containsKey(name)) {
            stats.put(name, 1);
            System.out.println("Welcome, " + name + "!");
        } else {
            stats.put(name, stats.get(name) + 1);
            System.out.println("Hello again(x" + stats.get(name) + "), " + name + "!");
        }
    }
}
