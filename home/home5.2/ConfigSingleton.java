import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class ConfigSingleton {
    private static ConfigSingleton instance;
    private Map<Character, String[]> configMap;

    private ConfigSingleton() {
        configMap = new HashMap<>();
        loadConfig();
    }

    public static synchronized ConfigSingleton getInstance() {
        if (instance == null) {
            instance = new ConfigSingleton();
        }
        return instance;
    }

    private void loadConfig() {
        try (BufferedReader br = new BufferedReader(new FileReader("config.txt"))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] parts = line.split(" ");
                String range = parts[0];
                String preWord = parts[1];
                String postWord = parts[2];
                for (char c = range.charAt(0); c <= range.charAt(2); c++) {
                    configMap.put(c, new String[]{preWord, postWord});
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public String[] getPrePostWords(char c) {
        return configMap.getOrDefault(c, new String[]{"defaultPre", "defaultPost"});
    }
}
