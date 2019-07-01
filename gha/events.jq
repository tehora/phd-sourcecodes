def out(x): tostring | output(x) | empty;

def issues: try fromjson | if .repo.name then (.created_at+";"+.actor.login+";"+.actor.gravatar_id+";"+(.actor.id|tostring)+";"+.repo.name+";"+";"+.org.login+";"+.payload.action+";"+(.payload.issue.id|tostring)) | out("../../agregates/gha/issuevent/issues1.csv") elif .actor_attributes.login or .actor_attributes.gravatar_id then if .repository.name then (.created_at+";"+.actor_attributes.login+";"+.actor_attributes.gravatar_id+";"+";"+.repository.name+";"+.repository.owner+";"+.organization+";"+.payload.action+";"+(.payload.issue|tostring)) | out("../../agregates/gha/issuevent/issues2.csv") else (.created_at+";"+.actor_attributes.login+";"+.actor_attributes.gravatar_id+";"+";"+.url+";"+";"+.organization+";"+.payload.action+";"+(.payload.issue|tostring))| out("../../agregates/gha/issuevent/issues4.csv") end else (.created_at+";"+.actor+";"+";"+";"+.repository.name+";"+.url+";"+.organization+";"+.payload.action+";"+(.payload.issue|tostring)) | out("../../agregates/gha/issuevent/issues3.csv") end;

def isbody: try fromjson | .created_at+";"+.actor.login+";"+.actor.gravatar_id+";"+(.actor.id|tostring)+";"+.repo.name+";"+";"+.org.login+";"+.payload.action+";"+.payload.issue.body | out("../../agregates/gha/bodyissues/body1.csv");

def comments: try fromjson | if .repo.name then (.created_at+";"+.actor.login+";"+.actor.gravatar_id+";"+(.actor.id|tostring)+";"+.repo.name+";"+";"+.org.login+";"+.payload.comment.body+";"+(.payload.issue.id|tostring)) | out("../../agregates/gha/commentevent/comments1.csv") elif .actor_attributes.login or .actor_attributes.gravatar_id then if .repository.name then (.created_at+";"+.actor_attributes.login+";"+.actor_attributes.gravatar_id+";"+";"+.repository.name+";"+.repository.owner+";"+.organization+";"+";"+(.payload.issue_id|tostring)) | out("../../agregates/gha/commentevent/comments2.csv") else (.created_at+";"+.actor_attributes.login+";"+.actor_attributes.gravatar_id+";"+";"+.url+";"+";"+.organization+";"+""+";"+(.payload.issue_id|tostring))| out("../../agregates/gha/commentevent/comments4.csv") end else (.created_at+";"+.actor+";"+";"+";"+.repository.name+";"+.url+";"+.organization+";"+";"+(.payload.issue|tostring)) | out("../../agregates/gha/commentevent/comments3.csv") end;

def commentstest: try fromjson | if .repo.name then (.created_at+";"+.actor.login+";"+.actor.gravatar_id+";"+(.actor.id|tostring)+";"+.repo.name+";"+";"+.org.login+";"+.payload.comment.body+";"+(.payload.issue.id|tostring)) | out("test1.csv") elif .actor_attributes.login or .actor_attributes.gravatar_id then if .repository.name then (.created_at+";"+.actor_attributes.login+";"+.actor_attributes.gravatar_id+";"+";"+.repository.name+";"+.repository.owner+";"+.organization+";"+";"+(.payload.issue_id|tostring)) | out("test2.csv") else (.created_at+";"+.actor_attributes.login+";"+.actor_attributes.gravatar_id+";"+";"+.url+";"+";"+.organization+";"+""+";"+(.payload.issue_id|tostring))| out("test4.csv") end else (.created_at+";"+.actor+";"+";"+";"+.repository.name+";"+.url+";"+.organization+";"+";"+(.payload.issue|tostring)) | out("test3.csv") end;

def orig_comments: try fromjson | (.payload.issue.created_at+";"+.payload.user.login+";"+.payload.user.gravatar_id+";"+(.payload.user.id|tostring)+";"+.repo.name+";"+";"+.org.login+";"+.payload.issue.body+";"+(.payload.issue.id|tostring)) | out("../../agregates/gha/commentevent/orig_comments1.csv");

def orig_titles: try fromjson | (.payload.issue.created_at+";"+.payload.user.login+";"+.payload.user.gravatar_id+";"+(.payload.user.id|tostring)+";"+.repo.name+";"+";"+.org.login+";"+.payload.issue.title+";"+(.payload.issue.id|tostring)) | out("../../agregates/gha/commentevent/orig_titles1.csv");

def pulls: try fromjson | if .repo.name then (.created_at+";"+.actor.login+";"+.actor.gravatar_id+";"+(.actor.id|tostring)+";"+.repo.name+";"+.payload.pull_request.base.user.login+";"+(.payload.pull_request.base.user.id|tostring)+";"+.payload.pull_request.base.user.gravatar_id+";"+.org.login+";"+.payload.action+";"+(.payload.pull_request.id|tostring)+";"+(.payload.pull_request.deletions|tostring)+";"+(.payload.pull_request.additions|tostring)+";"+(.payload.pull_request.commits|tostring)+";"+(.payload.pull_request.changed_files|tostring)+";"+.payload.pull_request.merged_at) | out("../../agregates/gha/pullevent/pulls1.csv") elif .payload.pull_request.user.login == null then (.created_at+";"+.actor_attributes.login+";"+.actor_attributes.gravatar_id+";"+";"+.repository.name+";"+.repository.owner+";"+(.payload.pull_request.base.user.id|tostring)+";"+.payload.pull_requests.base.user.gravatar_id+";"+.repository.organization+";"+.payload.action+";"+(.payload.pull_request.id|tostring)+";"+(.payload.pull_request.deletions|tostring)+";"+(.payload.pull_request.additions|tostring)+";"+(.payload.pull_request.commits|tostring)+";"+(.payload.pull_request.changed_files|tostring)+";"+.payload.pull_request.merged_at) | out("../../agregates/gha/pullevent/pulls3.csv") else (.created_at+";"+.payload.pull_request.user.login+";"+.payload.pull_request.user.gravatar_id+";"+(.payload.pull_request.user.id|tostring)+";"+.repository.name+";"+.payload.pull_request.base.user.login+";"+(.payload.pull_request.base.user.id|tostring)+";"+.payload.pull_request.base.user.gravatar_id+";"+.repository.organization+";"+.payload.action+";"+(.payload.pull_request.id|tostring)+";"+(.payload.pull_request.deletions|tostring)+";"+(.payload.pull_request.additions|tostring)+";"+(.payload.pull_request.commits|tostring)+";"+(.payload.pull_request.changed_files|tostring)+";"+.payload.pull_request.merged_at) | out("../../agregates/gha/pullevent/pulls2.csv") end;

def foll: try fromjson | if .actor_attributes then (.created_at+";"+";"+.actor+";"+.actor_attributes.gravatar_id + ";" + (.payload.target.id|tostring)+";"+.payload.target.login+";"+.payload.target.gravatar_id) | out("../../agregates/gha/follevent/following2.csv") else (.created_at+";"+(.actor.id|tostring)+";"+.actor.login+";"+.actor.gravatar.id + ";" + (.payload.target.id|tostring)+";"+.payload.target.login+";"+.payload.target.gravatar_id) | out("../../agregates/gha/follevent/following1.csv") end;

def star: try fromjson | if .repo.name then (.created_at+";"+.actor.login+";"+.actor.gravatar_id+";"+(.actor.id|tostring)+";"+.repo.name+";"+";"+.org.login) | out("../../agregates/gha/starevent/starring1.csv") elif .actor_attributes then if .repository.name then (.created_at+";"+.actor_attributes.login+";"+.actor_attributes.gravatar_id+";"+";"+.repository.name+";"+.repository.owner+";"+.organization) | out("../../agregates/gha/starevent/starring2.csv") else (.created_at+";"+.actor_attributes.login+";"+.actor_attributes.gravatar_id+";"+";"+.url+";"+";"+.organization) | out("../../agregates/gha/starevent/starring4.csv") end else (.created_at+";"+.actor+";"+";"+";"+.repository.name+";"+.url+";"+.organization)| out("../../agregates/gha/starevent/starring3.csv") end;

def fork: try fromjson | if .repo.name then (.created_at+";"+.actor.login+";"+.actor.gravatar_id+";"+(.actor.id|tostring)+";"+.repo.name+";"+";"+.org.login) | out("../../agregates/gha/forkevent/forking1.csv") elif .actor_attributes then (.created_at+";"+.actor_attributes.login+";"+.actor_attributes.gravatar_id+";"+";"+.repository.name+";"+.repository.owner+";"+.organization) | out("../../agregates/gha/forkevent/forking2.csv") elif .repository.owner == "" then (.created_at+";"+.actor+";"+";"+";"+.repository.name+";"+.repository.organization+";"+.repository.organization)| out("../../agregates/gha/forkevent/forking3.csv") else (.created_at+";"+.actor+";"+";"+";"+.repository.name+";"+.repository.owner+";"+.repository.organization)| out("../../agregates/gha/forkevent/forking4.csv") end;


