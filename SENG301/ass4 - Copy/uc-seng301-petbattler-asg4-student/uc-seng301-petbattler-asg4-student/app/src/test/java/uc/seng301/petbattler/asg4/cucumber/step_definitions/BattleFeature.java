package uc.seng301.petbattler.asg4.cucumber.step_definitions;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.hibernate.SessionFactory;
import org.hibernate.cfg.Configuration;
import org.junit.jupiter.api.Assertions;
import org.mockito.Mockito;
import io.cucumber.java.BeforeAll;
import io.cucumber.java.en.And;
import io.cucumber.java.en.Given;
import io.cucumber.java.en.Then;
import io.cucumber.java.en.When;
import uc.seng301.petbattler.asg4.Game;
import uc.seng301.petbattler.asg4.accessor.PackAccessor;
import uc.seng301.petbattler.asg4.accessor.PetAccessor;
import uc.seng301.petbattler.asg4.accessor.PlayerAccessor;
import uc.seng301.petbattler.asg4.cli.CommandLineInterface;
import uc.seng301.petbattler.asg4.model.GamePet;
import uc.seng301.petbattler.asg4.model.Pack;
import uc.seng301.petbattler.asg4.model.Pet;
import uc.seng301.petbattler.asg4.model.Player;
import uc.seng301.petbattler.asg4.pets.PetGenerator;
import uc.seng301.petbattler.asg4.pets.PetService;
import uc.seng301.petbattler.asg4.battle.Team;
import uc.seng301.petbattler.asg4.battle.TeamList;

public class BattleFeature {
    
    private static PlayerAccessor playerAccessor;
    private static PackAccessor packAccessor;
    private static PetAccessor petAccessor;
    private static PetGenerator petGeneratorSpy;
    public static int petIncrement = 0;

    private static List<String> output;
    private static Game game;
    private static Runnable doLater;
    public static Queue<String> mockedInputQueue;

    @BeforeAll
    public static void before_or_after_all() {
        Logger.getLogger("org.hibernate").setLevel(Level.SEVERE);
        Configuration configuration = new Configuration();
        configuration.configure();
        SessionFactory sessionFactory = configuration.buildSessionFactory();
        playerAccessor = new PlayerAccessor(sessionFactory);
        packAccessor = new PackAccessor(sessionFactory);
        petAccessor = new PetAccessor(sessionFactory);

        // mock command line, so we can inject user interactions
        CommandLineInterface cli = Mockito.mock(CommandLineInterface.class);
        game = new Game(petGeneratorSpy, cli, sessionFactory);

        mockedInputQueue = new LinkedList<>();
        Mockito.when(cli.getNextLine()).thenAnswer(i -> {
            String response = mockedInputQueue.poll();
            System.out.println("mocked input provided: " + response);
            return response;
        });

        // Capture standard out to test and for debugging purposes
        output = new ArrayList<>();
        Mockito.doAnswer((i) -> {
            output.add(i.getArgument(0));
            System.out.println((String) i.getArgument(0));
            return null;
        }).when(cli).printLine(Mockito.anyString());
    }

    // AC1 - AC3
    @Given("I have 2 teams")
    public void i_have_2_teams() {
        game.loadDefault();
    }

    // AC1 - AC3
    @When("I start a battle between them")
    public void i_start_a_battle() {
        doLater = () -> game.battle("battle t1 t2");
    }

    // AC1
    @Then("the battle should start")
    public void the_battle_should_start() {
        doLater.run();
        Assertions.assertTrue(output.contains("Starting Battle: "));
    }


    // AC2
    @And("I wait for 20 turns")
    public void i_wait_for_20_turns() {
        for (int i = 0; i < 20; i++) {
            mockedInputQueue.add("");
        }
        doLater.run();
    }

    // AC2
    @Then("the battle should end")
    public void the_battle_should_end() {
        doLater.run();
        Assertions.assertTrue(output.contains("Game did not finish in 20 rounds. No winners this time..."));
    }

    // AC3
    @And("A team loses all their pets")
    public void a_team_loses_all_their_pets() {
        
        doLater.run();
    }

}
