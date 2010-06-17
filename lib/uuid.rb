require_relative '../ext/uuid'

class UUID
  include Comparable
  def to_s
    "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x" % @uuid
  end
end
