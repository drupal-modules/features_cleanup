<?php
/**
 * @file
 *   Features module drush integration.
 */

/**
 * Implements hook_drush_command().
 *
 * @See drush_parse_command()
 * for a list of recognized keys.
 *
 * @return
 *   An associative array describing your command(s).
 */
function features_cleanup_drush_command() {
  $items = array();

  $items['features-cleanup-feature'] = array(
    'description' => "Attempts to resolve all overrides on a single feature module.",
    'arguments' => array(
      'feature' => 'The a space-delimited list of features.',
    ),
    'drupal dependencies' => array('features', 'diff', 'features_cleanup'),
    'aliases' => array('fcf'),
  );

  $items['features-cleanup-all'] = array(
    'description' => "Cleans out all content types, panel pages, mini panels, vocabularies, and image styles from database based on existing enabled features.",
    'drupal dependencies' => array('features', 'diff', 'features_cleanup'),
    'aliases' => array('fca'),
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 */
function features_cleanup_drush_help($section) {
  switch ($section) {
    case 'drush:features-cleanup-feature':
      return dt("Attempts to resolve all overrides by removing fields from the database. Requires 1 argument: feature name. For example drush features-resolve-overrides views_feature will attempt to resolve all field overrides for the feature named views_feature.");
    case 'drush:features-cleanup-all':
      return dt("Cleans out all content types, panel pages, mini panels, vocabularies, and image styles from database based on existing enabled features.");
  }
}

/**
 * Get a list of all feature modules.
 */
function drush_features_cleanup_feature() {
  if ($args = func_get_args()) {
    drush_print(dt('Fields that are not in the feature - but attached to a content type in the given feature - will PERMANENTLY be deleted: !modules', array('!modules' => implode(', ', $args))));
    if (drush_confirm(dt('Do you really want to continue?'))) {
      foreach ($args as $module_name) {
        module_load_include('inc', 'features', 'features.export');
        $feature = features_get_features($module_name);
        try {
          features_cleanup_override_perform($feature);
          drush_backend_invoke('features-revert ' . $module_name);
          drush_print(dt('The !module_name feature was successfully cleaned and reverted.', array('!module_name' => $module_name)));
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

function drush_features_cleanup_all() {
  drush_print(dt('Running this command will delete content types, panel pages, mini panels, image styles, and vocabularies based on existing ENABLED features. Please enable all desired features before running this command.'));
  if (drush_confirm(dt('Do you really want to continue?'))) {
    try {
      if (features_cleanup_perform()) {
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
