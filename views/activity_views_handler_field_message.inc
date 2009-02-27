<?php
// $Id:$
/**
 * @file: renders the message field for the given user
 */
class activity_views_handler_field_message extends views_handler_field {
  
  /**
   * override the render function
   */
  function render($values) {
    if ($GLOBALS['user']->uid == $values->{$this->aliases['uid']}) {
      return $values->{$this->aliases['author_message']};
    }
    else {
      return $values->{$this->field_alias};
    }
  }
}