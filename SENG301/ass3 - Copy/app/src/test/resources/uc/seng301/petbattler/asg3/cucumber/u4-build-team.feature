Feature: U4 As Alex, I want to create a Team from the pets in one of my packs so that I can use it in a battle.

  Scenario: AC1 - A pack must contain at least one pet to build a team with
    Given I create a player named "Monica Bing-Geller"
    And Player "Monica Bing-Geller" has an empty pack with the name "My Empty Pack"
    When I, "Monica Bing-Geller", try to build a team with "My Empty Pack"
    Then I am informed that the pack must have at least one pet

  Scenario: AC2 - When building a team there will be 5 options randomly selected from my pack
    Given I create a player named "Ross"
    And Player "Ross" has a pack "My 5 Pet Pack" with 5 unique pets
    When I, "Ross", try to build a team with "My 5 Pet Pack"
    Then I am given 5 options to choose

  Scenario: AC3 - When building a team I must select 3 options
    Given I create a player named "Rachel"
    And Player "Rachel" has a pack "NewPack" with 3 unique pets
    When I, "Rachel", try to build a team with "NewPack"
    And I do not choose three pets
    Then I am informed I must choose three pets

  Scenario: AC4 - When building a team I must select 3 unique pets
    Given I create a player named "Chandler"
    And Player "Chandler" has a pack "pack3" with 3 unique pets
    When I, "Chandler", try to build a team with "pack3"
    And I choose the same pet twice
    Then I am informed I must choose three unique pets
  
  Scenario: AC5 - When building a team and I select 3 unique options then my team is ordered the same way i entered my options
    Given I create a player named "Joey"
    And Player "Joey" has a pack "pack3" with 4 unique pets
    When I, "Joey", try to build a team with "pack3"
    And I choose 3 unique pets
    Then my team is ordered the same way I entered my options
  
  Scenario: AC6 - When building a team and I select options of all the same pet type they are different copies from those in my pack
    Given I create a player named "Phoebe"
    And Player "Phoebe" has a pack "My1PetPack" with 1 unique pets
    When I, "Phoebe", try to build a team with "My1PetPack"
    And I choose 3 of the same pet type
    Then my team is made up of different copies of the same pet type