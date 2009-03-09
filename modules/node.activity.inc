<?php
// $Id: $

/**
 * @file
 * Activity definition file for node.module
 */

/**
 * Implementation of hook_activity_info().
 */
function node_activity_info() {
  $info = new stdClass();
  $info->name = 'node';
  $info->object_type = 'node';
  $info->hooks = array('nodeapi' => array('presave', 'delete', 'insert', 'update', 'view'));
  $module_info[$info->name] = $info;
  return $module_info;
}

/**
 * Token module integration. Defines available default tokens.
 */
function node_activity_token_list($type = 'all') {
  if ($type == 'node') {
    $tokens['node'] = array(
      'node-link' 	=> t('Link to the post'),
      'node-type' 	=> t('The node type of the post'),
    );
    return $tokens;
  }
}

/**
 * Token module integration. Defines available default token values.
 */
function node_activity_token_values($type, $node = NULL, $options = array()) {
  if ($type == 'node' && !empty($node)) {
    $data['node-link'] = l($node>title, 'node/'. $node->nid);
    $data['node-type'] = theme('activity_node_type', $node->type);
    return $data;
  }
}