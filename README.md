Features Cleanup
----------------
Features Cleanup is a module that is to be used as an addendum to [Features][1].
does a good job of capturing and reverting existing components
(fields, panels, etc), it does not do a good job of deleting existing database
components that are not defined in a feature.

Features Cleanup is bridges this gap. Being a potentially dangerous module
(Features Cleanup can irrevertibly delete database components), Features Cleanup
can be used with best practices in mind. Using the Drush commands with a
tested deployment plan and scripts is the recommended usage guideline, with
GUI tools that are integrated with the Features interface as a secondary
and supported method of cleaning up your database.


Installation
------------
Features Cleanup can be installed like any other Drupal module -- place it in the
modules directory for your site and enable it on the `admin/build/modules` page.
To take full advantage of some of the workflow benefits provided by Features Cleanup,
you should install [Drush][2].

Features and the Diff module are required.


Basic usage
-----------
Features Cleanup is separted out into two different tasks.

### Task 1: Resolve Overrides

If you are having issues with running features-revert on a feature, and it's still
showing an overridden state, you can navigate to "Resolve Overrides" in the
Feature's overview screen, and click on "Resolve All Overrides" at the bottom.
Please backup your database and code before you do this, as it will attempt to
cleanup all overrides by deleting existing database components (namely, fields)
to resolve all overrides. After it does this, it will revert to this feature.

### Task 2: Delete existing components that are not in any Features modules

Features Cleanup can also delete:

- Content Types
- Mini Panels
- Node Panels
- Vocabularies
- Image Styles

You *MUST* enable all features you want to compare against before running the
cleanup operation. To run the Cleanup operation, click on "Features Cleanup"
in the Features listing screen.


Drush usage
-----------
Features Cleanup provides several useful drush commands:

- `drush fca`/`drush features-cleanup-all`

  Cleans out all content types, panel pages, mini panels, vocabularies, and image styles
  from database based on existing enabled features.

  Note: This will run features-revert-all afterwards.

- `drush fcf`/`drush features-cleanup-feature [feature name] [component list]`

  Attempts to resolves all overrides on a single feature module
  that have lingering override issues.  then run features-revert afterwards.
  You may specify a component list (for example, the content type).

  Note: This drush command will run features-revert on the given feature.

Compatibility
-------------
Features Cleanup provides integration for the following exportables:

- Image Styles
- Content Types
- Fields
- Vocabularies (Not Taxonomy Terms)
- Mini Panels
- Node Panels


Maintainers
-----------
- Paul Kim Consulting (Paul Kim)
- shawn.smiley (Shawn Smiley)
- csevb10 (Bill O'Connor)

Sponsored by: Achieve Internet (http://www.achieveinternet.com)

Homepage
--------

- https://www.drupal.org/sandbox/PaulKimConsulting/1342954
- https://github.com/drupal-modules/features_cleanup


[1]: http://drupal.org/project/features
[2]: http://drupal.org/project/drush
