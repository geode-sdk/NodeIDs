#define verifyIDSafe(Member_, ID_) \
    if(Member_ && Member_->getID() != ID_) { \
        log::warn(#Member_" has an invalid ID - {} (expected {})", Member_->getID(), ID_); \
    }