<?php
// $Id:$
/**
 * @file: provides views data integration for activity module as the base table
 */

/**
 * Implementation of hook_views_data().
 */
function activity_views_data() {
  $data['activity_messages']['table']['group'] = t('Activity');
  
  $data['activity_messages']['table']['base'] = array(
    'field' => 'amid',
    'title' => t('Activity'),
    'help' => t('Activity are items that are recorded for a users activity within the site'),
  );
  
  // Database columns
  $data['activity_messages']['uid'] = array(
    'title' => t('Activity Doer'),
    'help' => t('The ID of the person who recorded the activity'),
    'argument' => array(
      'handler' => 'views_handler_argument_user_uid',
    ),
    'filter' => array(
      'title' => t('Name'),
      'handler' => 'views_handler_filter_user_name',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['activity_messages']['op'] = array(
    'title' => t('Operation'),
    'help' => t('The operation being performed (update, insert, etc.)'),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['activity_messages']['type'] = array(
    'title' => t('Type'),
    'help' => t('The type of object being acted upon (node, user, etc.)'),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['activity_messages']['everyone_message'] = array(
    'title' => t('Activity Message'),
    'help' => t('The message generated by the activity'),
    'field' => array(
      'handler' => 'activity_views_handler_field_message',
      'additional fields' => array(
        'author_message',
        'uid',
      ),
    ),
  );
  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function activity_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'activity') . '/views',
    ),
    'handlers' => array(
      'activity_views_handler_field_message' => array(
        'parent' => 'views_handler_field',
      ),
    ),
  );
}