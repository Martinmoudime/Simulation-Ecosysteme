/**
 * @file EventTypes.h
 * @brief Définition des types d'événements du système
 * @author Martin
 * @date 2025/12/19
 */

#ifndef EVENT_TYPES_H
#define EVENT_TYPES_H

/**
 * @enum EventType
 * @brief Types d'événements possibles dans la simulation
 */
enum EventType
{
    EVENT_NONE,           /* Aucun événement */
    EVENT_QUIT,           /* Fermeture du programme */
    EVENT_COLLISION,      /* Collision entre deux entités */
    EVENT_DEATH,          /* Mort d'un animal */
    EVENT_BIRTH,          /* Naissance d'un animal */
    EVENT_PREDATION       /* Un prédateur mange une proie */
};

/**
 * @struct Event
 * @brief Structure représentant un événement
 */
struct Event
{
    EventType type;       /* Type de l'événement */
    void* data;          /* Données associées (optionnel) */
};

#endif /* EVENT_TYPES_H */
