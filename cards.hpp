//
//  minions.hpp
//  sorcery
//
//  Created by 马源浩 on 2017-11-22.
//  Copyright © 2017 马源浩. All rights reserved.
//

#ifndef minions_hpp
#define minions_hpp

#include "minion.hpp"
#include "enchantment.hpp"
#include "spell.hpp"
#include "ritual.hpp"
#include "ability.hpp"

#define Potion_Seller new Minion(true, "Potion Seller", "At the end of your turn, all your minions gain +0/+1", 2, 1, 3, 0, Key::AllAddah, Timer::End, 0, 1, 0, "");

#define Earth_Elemental new Minion(false, "Earth Elemental", "", 3, 4, 4, 0, Key::None, Timer::None, 0, 0, 0, "");

#define Bone_Golem new Minion(true, "Bone Golem", "Gain +1/+1 whenever a minion leaves play", 2, 1, 3, 0, Key::Addah, Timer::Death, 1, 1, 0, "");

#define Fire_Elemental new Minion(true, "Fire Elemental", "Whenever an oppenent's minion enters play, deal 1 damage to it", 2, 2, 3, 0, Key::Damage, Timer::Enter, 0, 0, 1, "");

#define Air_Elemental new Minion(false, "Air Elemental", "", 0, 1, 1, 0, Key::None, Timer::None, 0, 0, 0, "");

#define Novice_Pyromancer new Minion(false, "Novice Pyromancer", "Deal 1 damage to target minion", 1, 0, 1, 3, Key::Damage, Timer::None, 0, 0 , 1, "");

#define Apprentice_Summoner new Minion(false, "Apprentice Summoner", "Summon a 1/1 air elemental", 1, 1, 1, 1, Key::Sum, Timer::None, 0, 0, 1, "Air Elemental");

#define Master_Summoner new Minion(false, "Master Summoner", "Summon up to three 1/1 air elementals", 3, 2, 3, 2, Key::Sum, Timer::None, 0, 0, 3, "Air Elemental");

#define Banish new Spell("Banish", "Destroy target minion or ritual", 2, Key::Kill, Timer::None, 0, 0, 0, "");

#define Unsummon new Spell("Unsummon", "Return target minion to its owner's hand", 1, Key::Return, Timer::None, 0, 0, 0, "");

#define Recharge new Spell("Recharge", "Your ritual gains 3 charges", 1, Key::Recharges, Timer::None, 0, 0, 3, "");

#define Disenchant new Spell("Disenchant", "Destroy the top enchantment on target minion", 1, Key::Remove, Timer::None, 0, 0, 0, "");

#define Raise_Dead new Spell("Raise Dead", "Resurrect the top minion in your graveyard and set its defence to 1", 1, Key::Resurrect, Timer::None, 0, 0, 0, "");

#define Blizzard new Spell("Blizzard", "Deal 2 damage to all minions", 3, Key::Alldamage, Timer::None, 0, 0, 2, "");

#define Dark_Ritual new Ritual("Dark Ritual", "At the start of your turn, gain 1 magic", 0, Key::Magic, Timer::Start, 0, 0, 1, "", 1, 5);

#define Aura_of_Power new Ritual("Aure of Power", "Whenever a minion enters play under your control, it gains +1/+1", 1, Key::Addah, Timer::Start, 1, 1, 0, "", 1, 4);

#define Standstill new Ritual("Standstill", "Whenever a minion enters play, destroy it", 3, Key::Kill, Timer::Enter, 0, 0, 0, "", 2, 4);

#define Silence new Enchantment("Silence", "Enchanted minion cannot use a bilities", 1, "");

#define Enrage new Enchantment("Enrage", "", 2, "*");

#define Giant_Strength new Enchantment("Giant Strength", "", 1, "+");

#endif /* minions_hpp */
