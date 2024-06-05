public class Main {
    public static void main(String[] args) {
        System.out.println("Program started.");

        if (args.length < 1 || args.length > 2) {
            System.err.println("Usage: java Main <name> [delete]");
            return;
        }

        String name = args[0];
        User user = new User();
        user.load();

        if (args.length == 2 && args[1].equals("delete")) {
            user.reset(name);
        } else if (name.equals("bread")) {
            user.reset(name);
        } else {
            user.greet(name);
        }

        user.save();
        System.out.println("Program finished.");
    }
}
