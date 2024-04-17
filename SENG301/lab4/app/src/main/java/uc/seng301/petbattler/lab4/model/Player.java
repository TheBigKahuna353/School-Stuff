package uc.seng301.petbattler.lab4.model;

import java.util.List;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.FetchType;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.OneToMany;
import jakarta.persistence.Table;


@Entity
@Table(name = "player")
public class Player {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    @Column(name = "player_id")
    private Long playerId;

    @OneToMany(fetch = FetchType.EAGER)
    @JoinColumn(name = "player_id")
    private List<Pack> packs;

    private String name;

    public Player() {
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(String.format("Player (%d): %s%n\tPacks:%n", playerId, name));
        for (Pack pack : packs) {
            sb.append(String.format("\t\tPack (%d): %s%n\t\t\tPets:%n", pack.getPackId(), pack.getName()));
            for (Pet pet : pack.getPets()) {
                sb.append(String.format("\t\t\t\tPet (%d): %s -- Attack: %d, Health %d%n",
                    pet.getPetId(), pet.getName(), pet.getAttack(), pet.getHealth()));
            }
        }
        return sb.toString();
    }
    
    public Long getPlayerId() {
        return playerId;
    }

    public String getName() {
        return name;
    }

    public List<Pack> getPacks() {
        return packs;
    }

}
