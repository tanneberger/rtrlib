/*
 * This file is part of RTRlib.
 *
 * RTRlib is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * RTRlib is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with RTRlib; see the file COPYING.LESSER.
 *
 * written by Fabian Holler, in cooperation with:
 * INET group, Hamburg University of Applied Sciences,
 * CST group, Freie Universitaet Berlin
 * Website: http://rpki.realmv6.org/
 */

#ifndef RTR_LPFST
#define RTR_LPFST
#include <inttypes.h>
#include "rtrlib/lib/ip.h"


/**
 * @brief lpfst_node.
 * @param prefix
 * @param len
 * @param rchild
 * @param lchild
 * @param parent
 * @param data
 */
typedef struct lpfst_node_t {
    ip_addr prefix;
    uint8_t len;
    struct lpfst_node_t* rchild;
    struct lpfst_node_t* lchild;
    struct lpfst_node_t* parent;
    void* data;
} lpfst_node;

/**
 * @brief Inserts new_node in the tree.
 * param[in] root Node were the inserting process starts.
 * @param[in] new_node node that will be inserted.
 * @param[in] level of the the node root in the tree.
 */
void lpfst_insert(lpfst_node* root, lpfst_node* new_node, const unsigned int level);

/**
 * @brief Search for the node with the longest prefix matching the passed ip prefix and prefix length.
 * param[in] root_node Node were the lookup process starts.
 * @param[in] ip_addr IP-Prefix.
 * @param[in] mask_len Length of the network mask of the prefix.
 * @param[in,out] level of the the node root in the tree. Is set to the level from the node that was found thats
 * matches.
 * the passed ip prefix and prefix length.
 * @returns A The lpfst_node with the longest prefix in the tree matching the passed ip prefix and prefix length.
 * @returns NULL if no node that matches the passed IP prefix and prefix length could be found in the tree.
 */
lpfst_node* lpfst_lookup(const lpfst_node* root_node, const ip_addr* prefix, const uint8_t mask_len,  unsigned int* level);

/**
 * @brief Search for a node with the same prefix an prefix length.
 * param[in] root_node Node were the lookup process starts.
 * @param[in] ip_addr IP-Prefix.
 * @param[in] mask_len Length of the network mask of the prefix.
 * @param[in,out] level of the the node root in the tree. Is set to the level from the node that was found thats.
 * @param[in] found Is true if a node which matches could be found, else found is set to false.
 * @return A node which matches the passed parameter (found==true).
 * @return the parent of the node where the lookup operation stops, (found==false.
 * @return NULL if root_node is NULL.
*/
lpfst_node* lpfst_lookup_exact(lpfst_node* root_node, const ip_addr* prefix, const uint8_t mask_len, unsigned int* level, bool* found);

/**
 * @brief Removes the passed IP-Prefix from the tree.
 * param[in] root Node were the inserting process starts.
 * @param[in] prefix Prefix that will removed from the tree.
 * @param[in] level of the the node root in the tree.
 * @returns Node that was removed from the tree.
 */
lpfst_node* lpfst_remove(lpfst_node* root_node, const ip_addr* prefix, const unsigned int level);


/**
 * @brief Detects if a node is a leaf in tree.
 * param[in] node lpfst_node.
 * @returns true if node is a leaf:
 * @returns false if node isn't a leaf.
 */
int lpfst_is_leaf(const lpfst_node* node);
int lpfst_get_children(const lpfst_node* root_node, lpfst_node*** array, unsigned int* len);
#endif
