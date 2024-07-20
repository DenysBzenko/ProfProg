import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.PrintStream;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class MainTest {

    private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
    private final ByteArrayOutputStream errContent = new ByteArrayOutputStream();
    private final PrintStream originalOut = System.out;
    private final PrintStream originalErr = System.err;
    private final String testFilename = "user.txt";

    @Before
    public void setUp() {
        System.setOut(new PrintStream(outContent));
        System.setErr(new PrintStream(errContent));
        File file = new File(testFilename);
        if (file.exists()) {
            file.delete();
        }
    }

    @After
    public void tearDown() {
        System.setOut(originalOut);
        System.setErr(originalErr);
    }

    @Test
    public void testMainNoArguments() {
        Main.main(new String[]{});
        assertEquals("Program started.\nUsage: java Main <name> [delete]\n", errContent.toString().trim());
    }

    @Test
    public void testMainWithName() {
        Main.main(new String[]{"John"});
        assertTrue(outContent.toString().contains("Welcome, John!"));
        assertTrue(outContent.toString().contains("Saved stats to file."));
    }

    @Test
    public void testMainWithNameTwice() {
        Main.main(new String[]{"John"});
        outContent.reset();
        Main.main(new String[]{"John"});
        assertTrue(outContent.toString().contains("Hello again(x2), John!"));
        assertTrue(outContent.toString().contains("Saved stats to file."));
    }

    @Test
    public void testMainWithDelete() {
        Main.main(new String[]{"John"});
        outContent.reset();
        Main.main(new String[]{"John", "delete"});
        assertTrue(outContent.toString().contains("Statistics reset for John."));
        assertTrue(outContent.toString().contains("Saved stats to file."));
    }

    @Test
    public void testMainWithBread() {
        Main.main(new String[]{"bread"});
        assertTrue(outContent.toString().contains("All history cleared."));
        assertTrue(outContent.toString().contains("Saved stats to file."));
    }
}
