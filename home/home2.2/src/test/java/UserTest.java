import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import java.io.File;
import java.io.FileWriter;
import java.util.Map;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class UserTest {
    private User user;
    private final String testFilename = "user.txt";

    @Before
    public void setUp() throws Exception {
        user = new User();
        File file = new File(testFilename);
        if (file.exists()) {
            file.delete();
        }
    }

    @After
    public void tearDown() throws Exception {
        File file = new File(testFilename);
        if (file.exists()) {
            file.delete();
        }
    }

    @Test
    public void testLoad() throws Exception {
        try (FileWriter writer = new FileWriter(testFilename)) {
            writer.write("John 1\n");
        }
        user.load();
        Map<String, Integer> stats = user.getStats();
        assertTrue(stats.containsKey("John"));
        assertEquals((int) stats.get("John"), 1);
    }

    @Test
    public void testSave() throws Exception {
        user.greet("John");
        user.save();
        File file = new File(testFilename);
        assertTrue(file.exists());
    }

    @Test
    public void testResetName() throws Exception {
        user.greet("John");
        user.save();
        user.reset("John");
        assertTrue(!user.getStats().containsKey("John"));
    }

    @Test
    public void testResetBread() throws Exception {
        user.greet("John");
        user.save();
        user.reset("bread");
        assertTrue(user.getStats().isEmpty());
    }

    @Test
    public void testGreetNewUser() {
        user.greet("John");
        assertEquals((int) user.getStats().get("John"), 1);
    }

    @Test
    public void testGreetExistingUser() {
        user.greet("John");
        user.greet("John");
        assertEquals((int) user.getStats().get("John"), 2);
    }
}
