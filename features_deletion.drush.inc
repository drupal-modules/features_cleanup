<?php
error_reporting(E_ERROR);
/**
 * @file
 *   Features module drush integration.
 */

/**
 * Implements hook_drush_command().
 * 
 * @See drush_parse_command() for a list of recognized keys.
 *
 * @return
 *   An associative array describing your command(s).
 */
function features_deletion_drush_command() {
  $items = array();

  $items['features-resolve-overrides'] = array(
    'description' => "List all the available features for your site.",
    'drupal dependencies' => array('features', 'features_deletion'),
    'aliases' => array('fro'),
  );

  $items['features-cleanup'] = array(
    'description' => "List all the available features for your site.",
    'drupal dependencies' => array('features', 'features_deletion'),
    'aliases' => array('fro'),
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 */
function features_deletion_drush_help($section) {
  switch ($section) {
    case 'drush:features-resolve-overrides':
      return dt("Attempts to resolve all overrides by removing fields from the database. Please run features-revert or features-revert-all after this command.");
    case 'drush:features-cleanup':
      return dt("Cleans out all content types, panel pages, mini panels, vocabularies, and image styles from database based on existing enabled features.");
  }


}

/**
 * Get a list of all feature modules.
 */
function drush_features_resolve_overrides() {
  if ($args = func_get_args()) {
    drush_print(dt('The following features will override their database component counterparts. Fields and panels that are not in the feature will PERMANENTLY be deleted: !modules', array('!modules' => implode(', ', $args))));
    if (drush_confirm(dt('Do you really want to continue?'))) {
      foreach ($args as $module_name) {
        module_load_include('inc', 'features', 'features.export');
        try {
          features_deletion_override_perform($module_name, NULL, TRUE);
          drush_print(dt('All overrides were successfully cleaned. Please revert this feature.'));
        }
        catch (Exception $e) {
          drush_die($e);
        }
      }
    }
    else {
      drush_die('Aborting.');
    }
  }
  else {
    drush_die('Please specify a feature to resolve overrides.');
  }
}

function drush_features_cleanup() {
    drush_print(dt('The following features will delete content types, panel pages, mini panels, image styles, and vocabularies based on existing ENABLED features. Please enable all desired features before running this command.'));
    if (drush_confirm(dt('Do you really want to continue?'))) {
        try {
          if (features_deletion_perform()) {
            drush_print(dt('All extraneous database components successfully cleaned.'));
          }
        }
        catch (Exception $e) {
          drush_die($e);
        }
    }
    else {
      drush_die('Aborting.');
    }
}
