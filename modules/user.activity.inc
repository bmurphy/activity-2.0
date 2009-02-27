<?php
// $Id: $

/**
 * @file
 * Activity definition file for user.module
 */

/**
 * Implementation of hook_activity_info().
 */
function user_activity_info() {
  $info = new stdClass();
  $info->name = 'user';
  $info->object_type = 'user';
  $info->hooks = array('user' => array('insert', 'update', 'login', 'logout', 'view'));
  $module_info[$info->name] = $info;
  return $module_info;
}

/**
 * Token module integration. Defines available default tokens.
 */
function user_activity_token_list($type = 'all') {
  if ($type == 'user') {
    $tokens['user'] = array(
      'user-possessive'  => t('Possessive pronoun indicating whose user profile page ("your" or "their").'),
      'user-name-link' => t('Username as a link of the person who performed the action.'),
      'target-user-uid'  => t('User Id of the user profile viewed if viewing a profile.'),
      'target-user-name' => t('Person whose user profile was viewed.'),
      'target-user-name-link' => t('Username as a link of the person whose profile was viewed.'),
    );
    return $tokens;
  }
}

/**
 * Token module integration. Defines available default token values.
 */
function user_activity_token_values($type, $account = NULL, $options = array()) {
  global $user;
  if ($type == 'user' && !empty($account)) {
    $data['possessive'] = ($user->uid == $account->uid) ? t('your') : t('their');
    $data['user-name-link'] = l(theme('activity_username', $user), 'user/'. $user->uid);
    $data['target-user-uid'] = $account->uid;
    $data['target-user-name'] = theme('activity_username', $account);
    $data['target-user-name-link'] = l(theme('activity_username', $account), 'user/'. $account->uid);
  }
  return $data;
}