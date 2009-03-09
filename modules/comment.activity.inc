<?php
// $Id: $

/**
 * @file
 * Activity definition file for comment.module
 */

/**
 * Implementation of hook_activity_info().
 */
function comment_activity_info() {
  $info = new stdClass();
  $info->name = 'comment';
  $info->object_type = 'comment';
  $info->hooks = array('comment' => array('insert', 'update'));
  $module_info[$info->name] = $info;
  return $module_info;
}

/**
 * Token module integration. Defines available default tokens.
 */
function comment_activity_token_list($type = 'all') {
  if ($type == 'comment') {
    $tokens['comment'] = array(
      'comment-cid'					=> t('The Id of the comment'),
      'comment-subject' 			=> t('The subject of the comment'),
      'comment-link'				=> t('Link to the comment'),
      'parent-node-author-uid' 		=> t('User Id of the person who authored the parent node'),
      'parent-node-author' 			=> t('Person who authored the parent node'),
      'parent-node-author-name'		=> t('The username of the person who authored the parent node'),
      'parent-node-id '  			=> t('The Id of the parent node'),
      'parent-node-link'  			=> t('Link to the parent node'),
      'parent-node-title'  			=> t('Title of the parent node'),
      'parent-node-type' 			=> t('The type of the parent node'),
      'parent-comment-author-uid' 	=> t('User Id of the person who authored the parent comment'),
      'parent-comment-author' 		=> t('Person who authored the parent comment'),
      'parent-comment-author-name' 	=> t('The username of the person who authored the parent comment'),
      'parent-comment-cid'			=> t('The Id of the parent comment'),
      'parent-comment-subject'		=> t('The subject of the parent comment'),
      'parent-comment-link'			=> t('Link to the parent comment'),
    );
    return $tokens;
  }
}

/**
 * Token module integration. Defines available default token values.
 */
function comment_activity_token_values($type, $comment = NULL, $options = array()) {
  if ($type == 'comment' && !empty($comment)) {
    // parent data could be node or comment. if a pid exists the parent is a comment.
    if ($comment->pid) {
      // parent is a comment
      $data['parent-id'] = $comment->pid;
      $data['parent-type'] = 'comment';
      $data['parent-title'] = db_result(db_query('SELECT subject FROM {comments} WHERE cid = %d', $comment->cid));
      $data['parent-link'] = l($data['parent-title'], 'node/'. $comment->nid, array('fragment' => 'comment-'. $comment->cid));
      $data['parent-author-uid'] = $comment->uid;
      $data['parent-author-name'] = $comment->author;
    }
    else {
      // parent is a node
      $data['parent-id'] = $data['parent-node-id'] = $comment->nid;
      $data['parent-type'] = 'node';
      $data['parent-node-type'] = theme('activity_node_type', db_result(db_query('SELECT type FROM {node} WHERE nid = %d', $comment->nid)));
      $data['parent-title'] = $data['parent-node-title'] = db_result(db_query('SELECT title FROM {node} WHERE nid = %d', $comment->nid));
      $data['parent-link'] = $data['parent-node-link'] = l($data['parent-title'], 'node/'. $comment->nid);
      $data['parent-author-uid'] = $data['parent-node-author-uid'] = db_result(db_query('SELECT uid FROM {node} WHERE nid = %d', $comment->nid));
      $data['parent-author-name'] = $data['parent-node-author-name'] = db_result(db_query('SELECT name FROM {users} WHERE uid = %d', $data['parent-node-author-uid']));
    }

    //comment data
    $data['comment-cid'] = $comment->cid;
    $data['comment-title'] = $comment->subject;
    $data['comment-link'] = l($data['comment-title'], 'node/'. $comment->nid, array('fragment' => 'comment-'. $comment->cid));
  }  
  return $data;
}