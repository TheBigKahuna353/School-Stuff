Feature: U5 As Alex, I want to be able to simulate a battle between two teams so that I can have my pets fighting

Scenario: AC1 - I can start a battle between two distinct teams
    Given I have two teams
    When I start a battle between them
    Then the battle should start

Scenario: AC2 - A battle can not last longer than 20 turns
    Given I have two teams
    When I start a battle between them
    And I wait for 20 turns
    Then the battle should end

Scenario: AC3 - The team who loses all their pets first loses the battle
    Given I have two teams
    When I start a battle between them
    And A team loses all their pets
    Then the other team should win the battle