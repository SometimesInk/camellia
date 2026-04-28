#ifndef CAMELLIA__TYPE_LINKED_LIST_H__
#define CAMELLIA__TYPE_LINKED_LIST_H__

struct cam_type_linked_list_node;

struct cam_type_linked_list_node {
  void *value;
  struct cam_type_linked_list_node *next;
};

#endif /* CAMELLIA__TYPE_LINKED_LIST_H__ */
