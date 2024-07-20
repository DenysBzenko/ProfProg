import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class MusicPlayer {

    enum State {
        INTRO, STARMAN, SHOW_MUST_GO_ON, LET_IT_BE, IN_THE_END
    }

    private static final Map<State, Map<String, State>> transitions = new HashMap<>();

    static {
        
        Map<String, State> introTransitions = new HashMap<>();
        introTransitions.put("dangerous", State.LET_IT_BE);
        introTransitions.put("fun", State.STARMAN);
        introTransitions.put("sad", State.IN_THE_END);
        transitions.put(State.INTRO, introTransitions);

        
        Map<String, State> starmanTransitions = new HashMap<>();
        starmanTransitions.put("silly", State.INTRO);
        starmanTransitions.put("dangerous", State.SHOW_MUST_GO_ON);
        starmanTransitions.put("fun", State.IN_THE_END);
        transitions.put(State.STARMAN, starmanTransitions);

        
        Map<String, State> showMustGoOnTransitions = new HashMap<>();
        showMustGoOnTransitions.put("sad", State.LET_IT_BE);
        showMustGoOnTransitions.put("fun", State.STARMAN);
        transitions.put(State.SHOW_MUST_GO_ON, showMustGoOnTransitions);

        
        Map<String, State> letItBeTransitions = new HashMap<>();
        letItBeTransitions.put("dangerous", State.INTRO);
        letItBeTransitions.put("silly", State.SHOW_MUST_GO_ON);
        transitions.put(State.LET_IT_BE, letItBeTransitions);
    }

    
    private State currentState;

    public MusicPlayer() {
        this.currentState = State.INTRO;
    }


    public void handleCommand(String command) {
        if (currentState == State.IN_THE_END) {
            System.out.println("But in the end, it doesn't even matter");
            System.exit(0);
        }

        State nextState = transitions.getOrDefault(currentState, new HashMap<>()).get(command);
        if (nextState != null) {
            currentState = nextState;
        }

        switch (currentState) {
            case INTRO:
                System.out.println("Intro");
                break;
            case STARMAN:
                System.out.println("Starman");
                break;
            case SHOW_MUST_GO_ON:
                System.out.println("Show must go on");
                break;
            case LET_IT_BE:
                System.out.println("Let it be");
                break;
            case IN_THE_END:
                System.out.println("But in the end, it doesn't even matter");
                System.exit(0);
                break;
        }
    }


    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        MusicPlayer player = new MusicPlayer();

        while (true) {
            System.out.print("Enter command (sad, fun, silly, dangerous): ");
            String command = scanner.nextLine();
            player.handleCommand(command);
        }
    }
}
