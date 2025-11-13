## Policy Settings in QorAI

These are QorAI specific group policies.

Our official documentation is [available here](https://support.qorai.app/hc/en-us/articles/360039248271-Group-Policy).

For information about adding a new policy, please see [this page](https://source.chromium.org/chromium/chromium/src/+/main:docs/enterprise/add_new_policy.md).

In a nutshell, the steps for adding a new policy in QorAI look like this:

1. Create a new .yaml file under `//qorai/components/policy/resources/templates/policy_definitions/QorAISoftware/` and list it in `qorai_policies.gni`. The name of the file itself will be the policy name. Chromium uses capital casing. For example, we have a policy for disabling QorAI Rewards called `QorAIRewardsDisable.yaml`. The name used for matching is `QorAIRewardsDisable`.
2. Update the properties in that file accordingly. You can look at some of the existing ones as an example OR you can [check out an example one that Chromium shares here](https://source.chromium.org/chromium/chromium/src/+/main:components/policy/resources/new_policy_templates/policy.yaml).
3. Go into `//qorai/browser/policy/qorai_simple_policy_map.h` and add your entry here. It'll be auto-generated as `policy::key::k` and then the policy name. With the above example, that would be `policy::key::kQorAIRewardsDisable`. You must map this to a profile preference (you must create a new one). That new preference is what you'll check in the code.
4. In the code where you want to check the profile preference, you can tell if it's set via policy by checking `prefs->IsManagedPreference(<profile_preference_key_here>)`. If this is set to true, you might want to have the UI display something like `"This setting is managed by your organization"` and have it be read-only.
5. Build the project like regular (`npm run build`).
6. You can build the policy templates using `npm run build -- --target=qorai/components/policy:pack_policy_templates`.
7. The group policy assets get output to `//out/<build_type_here>/qorai_policy_templates.zip`. You can open this up and inspect the registry and adm/admx files. There is also a `policy_templates.zip` - that is the raw output before the script at `//qorai/components/policy/pack_policy_templates.py` runs.

If rebuilding isn't picking up your policy, you can try to delete `//out/<build_type_here>/gen/components/policy/policy_constants.cc`. Rebuilding will trigger the rebuild for this file and your changes should be there.


## Troubleshooting

If you're getting an error similar to:

> ../../qorai/browser/policy/qorai_simple_policy_map.h:75:19: error: no member named 'kQorAISpeedreaderDisabled' in namespace 'policy::key'; did you mean 'kQorAIRewardsDisabled'?

It might be that the minimum Chromium version is not yet in use by QorAI via the YAML's `supported_on`.  In that case you will need to temporarily specify a lower version until QorAI updates to the newer version.
