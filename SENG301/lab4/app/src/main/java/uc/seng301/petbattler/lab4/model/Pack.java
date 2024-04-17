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
@Table(name = "pack")
public class Pack {
    
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    @Column(name = "pack_id")
    private Long packId;

    private String name;

    @OneToMany(fetch = FetchType.EAGER)
    @JoinColumn(name = "pack_id")
    private List<Pet> pets;

    public Pack() {
    }

    public Long getPackId() {
        return packId;
    }

    public String getName() {
        return name;
    }

    public List<Pet> getPets() {
        return pets;
    }
}
