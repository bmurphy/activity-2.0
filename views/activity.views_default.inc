<?php
// $Id: $

/**
 * Implementation of hook_views_default_views().
 *
 * Construct a basic default activity view that can be used as a basis for other
 * views.
 */
function activity_views_default_views() {
  $view = new view;
  $view->name = 'activity';
  $view->description = '';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'activity_messages';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'everyone_message' => array(
      'label' => 'Activity Message',
      'exclude' => 0,
      'id' => 'everyone_message',
      'table' => 'activity_messages',
      'field' => 'everyone_message',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('items_per_page', 0);
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'activity-all');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'weight' => 0,
  ));
  $views[$view->name] = $view;
  return $views;
}